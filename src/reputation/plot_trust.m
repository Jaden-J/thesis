% creates figure, plots trust data and saves to requested file
% author: Christophe VG

function plot_trust(data_file, image_file)
  global plot_colors;
  global plot_legend;
  
  global threshold;
  

  load(data_file);
  
  fh = figure;
  plot([0:size(trusts,1)-1], trusts, plot_colors, 'lineWidth', 10);
  hold on;
  plot([0, size(trusts,1)-1], [threshold, threshold], '-k', 'lineWidth', 10 )

  axis([0 size(trusts,1)-1 0 +1]);
  set(gca, 'ytick', 0:.1:1);  % make sure every 0.1 tick is shown

  legend([plot_legend; 'drempelwaarde'], 'location', 'southeast');
  legend('boxoff');
  xlabel('Aantal pakketten');
  ylabel('Vertrouwen tussen i en j');

  % prepare for and save to file
  set(findall(fh, '-property', 'fontsize'), 'fontsize', 24);
  print(image_file, '-tight', '-color');
  close(fh);
end
