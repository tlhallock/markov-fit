


p = struct;
p.f = @(x)(norm(x));

opts = struct;
opts.ep        = 1e-4;
opts.maxevals  = 100;
opts.maxits    = 100
opts.maxdeep   = 100;
opts.testflag  = 0;
opts.showits   = 1;
opts.globalmin = 0;
opts.tol       = .01;
opts.impcons   = 0;

lb = [0 ; 0];
ub = [5 ; 5];

[x, fmin, history] = direct(p, [lb  ub], opts);


