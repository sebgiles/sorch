function [] = chart(filename)
    A = importdata(filename);
    figure('Name',filename,'NumberTitle','off')
    plot(A(:,1))
    hold on
    plot(A(:,2))
    plot(A(:,3))
    ylim([0,1.1*max(max(A(:,2:3)))]);
    xlim([0, length(A)]);
    legend('show', {'lin', 'bin', 'sor'});
end
