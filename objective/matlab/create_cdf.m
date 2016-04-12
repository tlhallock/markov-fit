function [ summedCdf ] = create_cdf( stencil , numSamples)

summedCdf = struct();
summedCdf.stencil = stencil;
summedCdf.probs = zeros(1, stencil.N);
summedCdf.count = 0;

while summedCdf.count < numSamples
    index = stencil.unmap(normrnd(2, 1));
    if index > 0
        summedCdf.probs(index) = summedCdf.probs(index) + 1;
    end
    summedCdf.count = summedCdf.count + 1;
end



end



function [summedCdf] = addToCdf(summedCdf, x)
    index = stencil.unmap(x);
    if index > 0
        summedCdf.probs(index) = summedCdf.probs(index) + 1;
    end
    summedCdf.count = summedCdf.count + 1;
    


end
