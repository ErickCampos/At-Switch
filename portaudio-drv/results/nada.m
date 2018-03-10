hold off;
clear all;
close all;

load L_1click_long_0amp.txt;
load R_1click_long_0amp.txt;

load L_2click_rapid_0amp.txt;
load R_2click_rapid_0amp.txt;

load single_click_0amp.txt;

figure;
%suptitle('1 long click, unamplif.');
subplot(2,1,1);
	plot(abs(L_1click_long_0amp(49500:59499)), 'k:');
	hold on;
	plot(abs((diff(L_1click_long_0amp(49500:59499)))), 'b--');
	grid on;
	legend(' abs(x)', ' abs(x'')');
	xlim([0 6000])
	set(gca, 'XTick', 0:250:6000);
subplot(2,1,2);
	plot(abs(R_1click_long_0amp(48000:57999)), 'k:');
	hold on;
	plot(abs((diff(R_1click_long_0amp(48000:57999)))), 'r--');
	grid on;
	legend(' abs(x)', ' abs(x'')');
	xlim([0 6000])
	set(gca, 'XTick', 0:250:6000);

figure;
suptitle('1 long click, unamplif.');
	subplot(2,1,1);
		plot(abs(L_1click_long_0amp(49500:59499)), 'k:');
		hold on;
		plot(abs((diff(L_1click_long_0amp(49500:59499)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([1250 1350])
		set(gca, 'XTick', 0:10:6000);
	subplot(2,1,2);
		plot(abs(R_1click_long_0amp(48000:57999)), 'k:');
		hold on;
		plot(abs((diff(R_1click_long_0amp(48000:57999)))), 'r--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([1250 1350])
		set(gca, 'XTick', 0:10:6000);

figure;
suptitle('1 long click, unamplif.');
	subplot(2,1,1);
		plot(abs(L_1click_long_0amp(49500:59499)), 'k:');
		hold on;
		plot(abs(diff(diff(L_1click_long_0amp(49500:59499)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'''')');
		xlim([1250 1350])
		set(gca, 'XTick', 0:10:6000);
	subplot(2,1,2);
		plot(abs(R_1click_long_0amp(48000:57999)), 'k:');
		hold on;
		plot(abs(diff(diff(R_1click_long_0amp(48000:57999)))), 'r--');
		grid on;
		legend(' abs(x)', ' abs(x'''')');
		xlim([1250 1350])
		set(gca, 'XTick', 0:10:6000);
%% --------------------------------------------------------------
%close all;

figure;
suptitle('2 rapid clicks, unamplif.');
subplot(2,1,1)
	plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
	hold on;
	plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
	grid on;
	legend(' abs(x)', ' abs(x'')');
	xlim([0 6000])
	set(gca, 'XTick', 0:250:6000);
subplot(2,1,2)
	plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
	hold on;
	plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
	grid;
	legend(' abs(x)', ' abs(x'')');
	xlim([0 6000])
	set(gca, 'XTick', 0:250:6000);

figure;
suptitle('2 rapid clicks, unamplif.');
	subplot(2,2,1)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([1000 2300])
		set(gca, 'XTick', 0:250:6000);
	subplot(2,2,2)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([3000 4600])
		set(gca, 'XTick', 0:250:6000);
	subplot(2,2,3)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'')');
		xlim([1000 2500])
		set(gca, 'XTick', 0:250:6000);
	subplot(2,2,4)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'')');
		xlim([3200 5400])
		set(gca, 'XTick', 0:250:6000);

figure;
suptitle('2 rapid clicks, unamplif.');
	subplot(2,4,1)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([1125 1275])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,2)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([1950 2100])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,3)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([3250 3400])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,4)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs((diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'')');
		xlim([4350 4500])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,5) % ------------------
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'')');
		xlim([1100 1250])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,6)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'')');
		xlim([2200 2350])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,7)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'')');
		xlim([3475 3625])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,8)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs((diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'')');
		xlim([4900 5050])
		set(gca, 'XTick', 0:50:6000);

figure;
suptitle('2 rapid clicks, unamplif.');
	subplot(2,4,1)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs(diff(diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'''')');
		xlim([1125 1275])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,2)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs(diff(diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'''')');
		xlim([1950 2100])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,3)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs(diff(diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'''')');
		xlim([3250 3400])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,4)
		plot(abs(L_2click_rapid_0amp(51400:61399)), 'k:');
		hold on;
		plot(abs(diff(diff(L_2click_rapid_0amp(51400:61399)))), 'b--');
		grid on;
		legend(' abs(x)', ' abs(x'''')');
		xlim([4350 4500])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,5) % ------------------
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs(diff(diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'''')');
		xlim([1100 1250])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,6)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs(diff(diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'''')');
		xlim([2200 2350])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,7)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs(diff(diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'''')');
		xlim([3475 3625])
		set(gca, 'XTick', 0:50:6000);
	subplot(2,4,8)
		plot(abs(R_2click_rapid_0amp(50000:59999)), 'k:');
		hold on;
		plot(abs(diff(diff(R_2click_rapid_0amp(50000:59999)))), 'r--');
		grid;
		legend(' abs(x)', ' abs(x'''')');
		xlim([4900 5050])
		set(gca, 'XTick', 0:50:6000);
% ---------------------------------------------------------------------
%close all;

figure;
suptitle('1 rapid click, unamplif.');
subplot(2,4,[1,2,3,4])
	plot(abs(single_click_0amp(35400:45399)), 'k:');
	hold on;
	plot(abs((diff(single_click_0amp(35400:45399)))), 'b--' );
	grid on;
	xlim([0 6000])
	set(gca, 'XTick', 0:250:6000);
subplot(2,4,5)
	plot(abs(single_click_0amp(35400:45399)), 'k:');
	hold on;
	plot(abs(diff((single_click_0amp(35400:45399)))), 'b--' );
	grid on;
	legend(' abs(x)', ' abs(x'')');
	xlim([1175 1250])
	set(gca, 'XTick', 0:25:6000);
	title('1^{st} peak');
subplot(2,4,6)
	plot(abs(single_click_0amp(35400:45399)), 'k:');
	hold on;
	plot(abs((diff(single_click_0amp(35400:45399)))), 'b--' );
	grid on;
	legend(' abs(x)', ' abs(x'''')');
	xlim([1175 1250])
	set(gca, 'XTick', 0:25:6000);
	title('1^{st} peak');
subplot(2,4,7)
	plot(abs(single_click_0amp(35400:45399)), 'k:');
	hold on;
	plot(abs(diff(diff(single_click_0amp(35400:45399)))), 'm--' );
	grid on;
	legend(' abs(x)', ' abs(x'')');
	xlim([1875 1950])
	set(gca, 'XTick', 0:25:6000);
	title('2^{nd} peak');
subplot(2,4,8)
	plot(abs(single_click_0amp(35400:45399)), 'k:');
	hold on;
	plot(abs(diff(diff(single_click_0amp(35400:45399)))), 'm--' );
	grid on;
	legend(' abs(x)', ' abs(x'''')');
	xlim([1875 1950])
	set(gca, 'XTick', 0:25:6000);
	title('2^{nd} peak');

%%% EOF %%%
