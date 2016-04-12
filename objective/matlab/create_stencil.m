function [ stencil ] = create_stencil(start, stop, N)

stencil = struct();
stencil.start = start;
stencil.stop = stop;
stencil.N = N;
stencil.unmap = @(x) check_index_bounds(stencil, x);
stencil.map = @(i) (start + i/N * (stop - start));

end


function [index] = check_index_bounds(stencil, x)
    index = int32(1 + (N-1) * (x-start) / (stop - start));
    if index < 1 || index > stencil.N || x > stencil.stop || x < stencil.start
        index = -1;
    end
end


%function [index] = check_value_bounds(stencil, vl)
%    if index <= 0 || index > stencil.N
%        index = -1;
%    end
%end
