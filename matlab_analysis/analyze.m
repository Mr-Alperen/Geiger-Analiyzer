file = "log/geiger_log.txt";  % Log dosyası
data = readlines(file);

alpha_cpm = [];
gamma_cpm = [];
times = [];

for i = 1:length(data)
    line = data(i);
    if contains(line, "{")
        t = extractBetween(line, 1, 19);
        times(end+1) = datetime(t, 'InputFormat', 'yyyy-MM-dd HH:mm:ss');

        jsonStr = extractAfter(line, "| ");
        j = jsondecode(char(jsonStr));

        alpha_cpm(end+1) = j.alpha_cpm;
        gamma_cpm(end+1) = j.gamma_cpm;
    end
end

% Grafik
figure;
plot(times, alpha_cpm, '-r', 'LineWidth', 2); hold on;
plot(times, gamma_cpm, '-b', 'LineWidth', 2);
xlabel("Zaman");
ylabel("CPM");
legend("Alpha CPM", "Gamma CPM");
title("Demir Yumruk: Geiger Sayaç Radyasyon İzleme");
grid on;