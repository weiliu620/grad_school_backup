function C = EMPostReal(R, CMask, dir, sz1, sz2)
% Inherit from EMPost, but apply on real data.
% Given sample correlation matrix R,
% compute the posterior matrix C, where c_ij = p(c_ij|r_ij).
% EMethod:
% 1) 'sampling': 
% 2) 'Annealing': change T during iteration of sampling.
% 3) 'smf': first sampling, then iteratively compute mean field.
% 4) 'amf': first annealing, then iteratively compute mean field.
        
% init model parameters.
mu = [0 0.5]; % Bold guess. mu(1) is mean for noconnectivity.
sigma2 = [0.2 0.2]; % when A^2/sigma^2 is 10. Roughly guess.

% initialize
[M, N] = size(R); % number of voxels.
C = CudaInitGateway(R, mu,sigma2, CMask);
T = 5; % Annealing temperature.
beta = 1/T;
iterCount = 1;
para = [mu, sigma2]; % all parameters.
allPost = zeros(N, M, 2);
allBeta = beta;
change = inf;
maxMFIter = 5;
maxSAIterCount = 10;
while(change > 10^(-5))
    %%%%%%%%%%%%% E step. Compute posterior probability.  %%%%%%%%%%%%%
    
    C = CudaSamplingGateway(C, R, CMask,...
        mu, sigma2, beta, maxSAIterCount, sz1, sz2);
    
    % show connectivity map.
    figure(1); imshow((C+1)*0.5, 'InitialMagnification', 'fit');
    title(strcat('Posterior Connectivity: Sampled'));
    
    % compute mean field.
    C = CudaMeanField(C, R,...
        coord1, coord2,...
        mu(1), mu(2), sigma2(1), sigma2(2),...
        beta, maxSAIterCount);
    
    % show connectivity map.
    figure(1); imshow((C+1)*0.5, 'InitialMagnification', 'fit');
    title(strcat('Posterior Connectivity: Expected value'));

    % Now the field is stable (equililbrium). Save posterior for
    % estimating parameters.
    allPost = ELocalProb(C, R, mu, sigma2, beta);
    figure(11); imshow(allPost(:,:,1));
    title('Posterior map for C = 0 (no connectivity)');
    figure(12); imshow(allPost(:,:,2));
    title('Posterior map for C = 1 (have connectivity)');
    pause(0.01);
    
    %%%%%%%%%%%     M step. estimate parameters.   %%%%%%%%%%%%%
    % # of c = 0 in triangular matrix.
    Nk(1) = sum(sum(allPost(:,:,1)));
    Nk(2) = sum(sum(allPost(:,:,2))); % c = 1
    % mu(1) = 0. No change. 
    CR = allPost(:,:,2) .* R;
    CR = CR - diag(diag(CR));
    mu(2) = sum(CR(:))/Nk(2);
    
    RM1 = allPost(:,:,1) .* (R - mu(1)).^2; 
    RM2 = allPost(:,:,2) .* (R - mu(2)).^2; 
    sigma2(1) = sum(RM1(:))/Nk(1);
    sigma2(2) = sum(RM2(:))/Nk(2); 
    
    % Estimate beta. This need a lot of work. We begin with previous beta
    % as a init value for Newton's method.
    epsilon = 10^(-6);
    maxBeta =15;
    step = inf;    
    newBeta = beta;
        while (step > epsilon && newBeta < maxBeta)
            J = 0; DELL =0 ;
            for n = 1:N*M
                [i,j] = ind2sub([N M], n);
                neighbors = n + [-1 1 -N N];
                neighbors([i==1, i==N, j==1, j==M]) = [];
                nsum = sum(C(neighbors));
                J = J + nsum^2 * (tanh(beta*nsum)^2 - 1);
                DELL = DELL + nsum*(C(i,j) - tanh(beta*nsum)); %2nd deriv
            end;
            step = -DELL/J;
            newBeta = beta + step;
            if newBeta > maxBeta || isnan(newBeta)
                %fprintf('beta is already very large. Unchanged.\n');
                beta = 100;
                fprintf('beta set to 100\n');
            else
                beta = newBeta;
                fprintf('step = %d, new beta = %2.2f\n', step, beta);
            end;

            allBeta = [allBeta; beta];
            figure(2);
            plot(allBeta, 'ro-');
            title('Estimation of beta');
        end;
    
    % show the histogram.
    sel = logical(C < 0);
    R0 = R(sel);
    sel = logical(C > 0);
    R1 = R(sel);

    figure(3);
    hist(R0, Nk(1)/200);
    title('sample correlation given c = 0');
    figure (4); hist(R1, Nk(2)/20);
    title('sample correlation given c = 1');
    
    % save parameters and dispaly the trend.
    para = [para; [mu, sigma2]];
    change = sum(abs(para(end,:) - para(end-1,:))); % if change big, continue.
    Xcoord = 1:iterCount+1;
    figure(5);
    plot(Xcoord, para(:,1), 'bo-',...
        Xcoord, para(:,2), 'ro-',...
        Xcoord, para(:,3), 'b*--',...
        Xcoord, para(:,4),  'r*--');
    title('trend of parameters in EM iteration.');
    xlabel('EM iteration');
    legend('mu0', 'mu1', 'sgima^2 0', 'sigma^2 1');
    
    fprintf('iteration: %d\n', iterCount);
    iterCount = iterCount +1;        
end;

mysave(1, strcat(dir, 'postConnMap.eps'));
mysave(11, strcat(dir, 'postP0.eps'));
mysave(12, strcat(dir, 'postP1.eps'));
mysave(2, strcat(dir, 'beta.eps'));
mysave(3, strcat(dir, 'dond_corr0.eps'));
mysave(4, strcat(dir, 'dond_corr1.eps'));
mysave(5, strcat(dir, 'para_est.eps'));

function C = ESampling(C, R, mu, sigma2, beta)

[N, M] = size(C);
gc = 1./(sqrt(2*pi*sigma2)); % Gaussian constant.
coor = randperm(N*M);
for n = coor
    [i,j] = ind2sub([N M], n);
    neighbors = n + [-1 1 -N N];
    neighbors([i==1, i==N, j==1, j==M]) = [];
    nsum = sum(C(neighbors));
    denom = 2*cosh(beta*nsum);
    pr(1) = exp(beta*(-1)*nsum)/denom;
    pr(2) = exp(beta*(+1)*nsum)/denom;
    % Likelihood.
    lhood(2) = gc(2) * exp(-(R(i,j)-mu(2))^2/(2*sigma2(2)));
    lhood(1) = gc(1) * exp(-(R(i,j)-mu(1))^2/(2*sigma2(1)));
    % Posterior.
    post(1) = pr(1) * lhood(1);
    post(2) = pr(2) * lhood(2);
    % Normalize so they sum to one.
    post = post/sum(post);
    % Gibbs Sampling.
    if rand < post(1)
        C(i,j) = -1;
    else
        C(i,j) = 1;
    end;    
end;

function allPost = ELocalProb(C, R, mu, sigma2, beta)
% compute local posterior probability p(x | nbor(x))
[N, M] = size(C);
gc = 1./(sqrt(2*pi*sigma2)); % Gaussian constant.
allPost = zeros(N,M,2);
for n = 1:N*M
    [i,j] = ind2sub([N M], n);
    
    neighbors = n + [-1 1 -N N];
    neighbors([i==1, i==N|i==j-1, j==1|i==j-1, j==N]) = [];
    nsum = sum(C(neighbors));
    denom = 2*cosh(beta*nsum);
    pr(1) = exp(beta*(-1)*nsum)/denom;
    pr(2) = exp(beta*(+1)*nsum)/denom;
    % Likelihood.
    lhood(2) = gc(2) * exp(-(R(i,j)-mu(2))^2/(2*sigma2(2)));
    lhood(1) = gc(1) * exp(-(R(i,j)-mu(1))^2/(2*sigma2(1)));
    % Posterior.
    allPost(i,j, 1) = pr(1) * lhood(1);
    allPost(i,j, 2) = pr(2) * lhood(2);
    % Normalize so they sum to one.
    allPost(i,j,:) = allPost(i,j,:)/sum(allPost(i,j,:));    
end;

function C = EMeanField(C, R, mu, sigma2, beta, maxMFIter)
% mean field 
[N, M] = size(C);
gc = 1./(sqrt(2*pi*sigma2)); % Gaussian constant.
for k = 1:maxMFIter
    coor = randperm(N*M);
    for n = coor
        [i,j] = ind2sub([N M], n);
            neighbors = n + [-1 1 -N N];
            neighbors([i==1, i==N, j==1, j==M]) = [];
            nsum = sum(C(neighbors));
            denom = 2*cosh(beta*nsum);
            pr(1) = exp(beta*(-1)*nsum)/denom;
            pr(2) = exp(beta*(+1)*nsum)/denom;
            % Likelihood.
            lhood(2) = gc(2) * exp(-(R(i,j)-mu(2))^2/(2*sigma2(2)));
            lhood(1) = gc(1) * exp(-(R(i,j)-mu(1))^2/(2*sigma2(1)));
            % Posterior.
            post(1) = pr(1) * lhood(1);
            post(2) = pr(2) * lhood(2);
            % Normalize so they sum to one.
            post = post/sum(post);
            % we dont' sample from posterior. Instead we compute the
            % expected value. Mean field theory.
            C(i,j) = post(2) - post(1) ;
    end;
end;
