classdef benchResults
    %   benchResults - store sort benchmark results
    
    properties
        plotTitle
        benchSizes
        
        bubbleSort
        selectionSort
        insertionSort
        mergeSort
        mergeParallelSort
        quickSort
    end
    methods
        function plotBench(obj)
            hold on;
            grid on;
            grid minor;
            
            % Configure figure window
            ylabel("Time, ms");
            xlabel("Array size");
            title(obj.plotTitle);
            
            % Plotting interval
            x_plot = -1000:6e5;
            
            % Bubble sort, complexity - O(N^2)
            p = polyfit(obj.benchSizes, obj.bubbleSort, 2);
            f = polyval(p, x_plot);
            color = [rand, rand, rand];
            plot(x_plot, f, '-', 'Color', color, 'DisplayName', 'Bubble Sort Benchmark');
            plot(obj.benchSizes, obj.bubbleSort, 'x', 'Color', color, 'DisplayName', 'Bubble Sort Approximation');
        
            % Selection sort, complexity - O(N^2)
            p = polyfit(obj.benchSizes, obj.selectionSort, 2);
            f = polyval(p, x_plot);
            color = [rand, rand, rand];
            plot(x_plot, f, '-', 'Color', color, 'DisplayName', 'Selection Sort Benchmark');
            plot(obj.benchSizes, obj.selectionSort, 'x', 'Color', color, 'DisplayName', 'Selection Sort Approximation');
            
            % Insertion sort, complexity - O(N^2)
            p = polyfit(obj.benchSizes, obj.insertionSort, 2);
            f = polyval(p, x_plot);
            color = [rand, rand, rand];
            plot(x_plot, f, '-', 'Color', color, 'DisplayName', 'Insertion Sort Benchmark');
            plot(obj.benchSizes, obj.insertionSort, 'x', 'Color', color, 'DisplayName', 'Insertion Sort Approximation');
            
            % Merge Sort, complexity - O(N*log(N))
            color = [rand, rand, rand];
            plot(obj.benchSizes, obj.mergeSort, 'x', 'Color', color, 'DisplayName', 'Merge Sort Benchmark');
            % legend("Merge Sort")
            
            % Merge Sort Parallel, complexity - O(N*log(N))
            color = [rand, rand, rand];
            plot(obj.benchSizes, obj.mergeParallelSort, 'x', 'Color', color, 'DisplayName', 'Merge Parallel Sort Benchmark');
            
            % Quick Sort, complexity - O(N*log(N))
            color = [rand, rand, rand];
            plot(obj.benchSizes, obj.quickSort, 'x', 'Color', color, 'DisplayName', 'Quick Sort Benchmark');
            
            legend
            hold off;
        end
    end
end

