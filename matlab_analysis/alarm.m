% Anlık İzleme & Alarm
file = "log/geiger_log.txt";
alpha_threshold = 200; % CPM
gamma_threshold = 100; % CPM

persistent lastLineCount
if isempty(lastLineCount)
    lastLineCount = 0;
end

while true
    data = readlines(file);
    newLines = data(lastLineCount+1:end);
    if isempty(newLines)
        pause(1);
        continue;
    end

    alpha_cpm = [];
    gamma_cpm = [];
    times = [];

    for i = 1:length(newLines)
        line = newLines(i);
        if contains(line, "{")
            t = extractBetween(line, 1, 19);
            times(end+1) = datetime(t, 'InputFormat', 'yyyy-MM-dd HH:mm:ss');

            jsonStr = extractAfter(line, "| ");
            j = jsondecode(char(jsonStr));

            alpha_cpm(end+1) = j.alpha_cpm;
            gamma_cpm(end+1) = j.gamma_cpm;
        end
    end

    figure(1);
    plot(times, alpha_cpm, '-r', 'LineWidth', 2); hold on;
    plot(times, gamma_cpm, '-b', 'LineWidth', 2);
    xlabel("Zaman");
    ylabel("CPM");
    legend("Alpha CPM", "Gamma CPM");
    title("Demir Yumruk: Anlık Geiger İzleme");
    grid on;
    drawnow;

    % Alarm kontrolü
    if any(alpha_cpm > alpha_threshold)
        disp("⚠️ Alpha CPM eşik aşıldı!");
    end
    if any(gamma_cpm > gamma_threshold)
        disp("⚠️ Gamma CPM eşik aşıldı!");
    end

    lastLineCount = length(data);
    pause(1);
end