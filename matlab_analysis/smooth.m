function y = smooth_data(x, windowSize)
% Moving average filtresi
    y = movmean(x, windowSize);
end