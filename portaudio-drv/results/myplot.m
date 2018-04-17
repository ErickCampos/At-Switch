load out;

x = abs(out);

figure;
plot(x); grid on; hold on;
set(gca, 'XTick', 0:250:7000);
set(gca, 'YTick', 0:1000:20000);

chunks = [500 1000 1250 1375 1437];
for i = chunks
	stem(i, x(i), 'r--', 'markerfacecolor', 'r', 'linewidth', 2);
end

chunks = [500 1000 1250 1375 1437]+1000;
for i = chunks
	stem(i, x(i), 'k--', 'markerfacecolor', 'k', 'linewidth', 2);
end

figure;
plot(x); grid on; hold on;
set(gca, 'XTick', 0:100:7000);
set(gca, 'YTick', 0:1000:20000);

chunks = [500 1000 1250 1375 1437];
for i = chunks
	stem(i, x(i), 'r--', 'markerfacecolor', 'r', 'linewidth', 2);
end

chunks = [500 1000 1250 1375 1437]+1000;
for i = chunks
	stem(i, x(i), 'k--', 'markerfacecolor', 'k', 'linewidth', 2);
end
xlim([300 2800]);
