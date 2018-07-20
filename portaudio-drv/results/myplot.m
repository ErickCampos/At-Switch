clear all;
hold off;
close all;

load out;

x = abs(out);

figure;
a = plot(x, 'b-', 'LineWidth', 2);
hold on;
%grid on;
set(gca, 'XTick', 0:250:7000  , 'FontSize', 18);
set(gca, 'YTick', 0:1000:20000, 'FontSize', 18);

plot(ones(1,length(0:5500))*1000, 'k--');
xlim([0 5000]);

chunks = [500 1000 1250 1375 1437];
for i = chunks
	b = stem(i, x(i), 'ro--', 'markersize', 8, 'markerfacecolor', 'r', 'linewidth', 2);
end

chunks = [500 1000 1250 1375 1437]+1500;
for i = chunks
	c = stem(i, x(i), 'ks--', 'markersize', 10, 'markerfacecolor', 'k', 'linewidth', 2);
	if x(i) < 1000
		chunks = [500 1000 1250 1375 1437]+500+i;
		for j = chunks
			d = stem(j, x(j), 'md--',  'markersize', 10,'markerfacecolor', 'm', 'linewidth', 2);
		end
		break;
	end
end

l = legend([b c d],...
	'Teste 1: sucesso, sopro',...
	'Teste 2: falha, não-sopro',...
	'Teste 3: recuperação do teste 2');
set(l, 'FontSize', 24);

xlabel('Amostras',  'FontSize', 40);
ylabel('Amplitude', 'FontSize', 40);

return; % ----------------------------------------------------------------------

figure;
plot(x, 'LineWidth', 2); grid on; hold on;
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

xlabel('Amostras',  'FontSize', 20);
ylabel('Amplitude', 'FontSize', 20);
