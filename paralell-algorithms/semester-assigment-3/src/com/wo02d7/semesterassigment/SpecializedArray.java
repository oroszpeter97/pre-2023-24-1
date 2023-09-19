package com.wo02d7.semesterassigment;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class SpecializedArray {
    private int _arrayLength;
    private int _valueLowerLimit;
    private int _valueUpperLimit;
    private int _numberOfThreads;
    private int _sum;
    private double _prod;
    private int _minIndex;
    private int _maxIndex;
    private int[] _array;
    private Range[] _ranges;

    public SpecializedArray(int arrayLength, int valueLowerLimit, int valueUpperLimit, int numberOfThreads){
        this._arrayLength = arrayLength;
        this._valueLowerLimit = valueLowerLimit;
        this._valueUpperLimit = valueUpperLimit;
        this._numberOfThreads = numberOfThreads;
        CalculateRanges();
    }

    public void GenerateArray() {
        _array = new int[_arrayLength];
        ExecutorService executor = Executors.newFixedThreadPool(_numberOfThreads);

        for(int i = 0; i < _numberOfThreads; i++){
            executor.execute(new GenerateArrayTask(_array, _ranges[i].GetLowerRange(), _ranges[i].GetUpperRange(), _valueLowerLimit, _valueUpperLimit));
        }

        executor.shutdown();
        while (!executor.isTerminated()){} // Wait for all threads to finish
    }

    public void SumArray(){
        List<Integer> _threadSums = new ArrayList<Integer>();
        List<Future<Integer>> futures = new ArrayList<>();
        _sum = 0;
        ExecutorService executor = Executors.newFixedThreadPool(_numberOfThreads);

        // Start threads
        for(int i = 0; i < _numberOfThreads; i++){
            SumArrayRangeTask task = new SumArrayRangeTask(_array, _ranges[i].GetLowerRange(), _ranges[i].GetUpperRange());
            Future<Integer> future = executor.submit(task);
            futures.add(future);
        }
        
        // Process the return values of the tasks
        for (int i = 0; i < futures.size(); i++) {
            try {
                int sum = futures.get(i).get();
                _threadSums.add(sum);
            } catch (InterruptedException | ExecutionException e) {
                System.out.println("An error occurred while retrieving the result: " + e.getMessage());
            }
        }

        // Sum each threads result
        for(int i = 0; i < _threadSums.size(); i++){
            _sum += _threadSums.get(i);
        }

        executor.shutdown();
        while (!executor.isTerminated()){} // Wait for all threads to finish
    }

    public void ProdArray(){
        List<Double> _threadProds = new ArrayList<Double>();
        List<Future<Double>> futures = new ArrayList<>();
        _prod = 1.0;
        ExecutorService executor = Executors.newFixedThreadPool(_numberOfThreads);

        // Start threads
        for(int i = 0; i < _numberOfThreads; i++){
            ProdArrayRangeTask task = new ProdArrayRangeTask(_array, _ranges[i].GetLowerRange(), _ranges[i].GetUpperRange(), _valueLowerLimit, _valueUpperLimit);
            Future<Double> future = executor.submit(task);
            futures.add(future);
        }
        
        // Process the return values of the tasks
        for (int i = 0; i < futures.size(); i++) {
            try {
                Double prod = futures.get(i).get();
                _threadProds.add(prod);
            } catch (InterruptedException | ExecutionException e) {
                System.out.println("An error occurred while retrieving the result: " + e.getMessage());
            }
        }

        // Prod each threads result
        for(int i = 0; i < _threadProds.size(); i++){
            _prod *= _threadProds.get(i);
        }

        executor.shutdown();
        while (!executor.isTerminated()){} // Wait for all threads to finish
    }

    public void FindMinIndexInArray(){
        List<Integer> _threadMins = new ArrayList<Integer>();
        List<Future<Integer>> futures = new ArrayList<>();
        _minIndex = 0;

        ExecutorService executor = Executors.newFixedThreadPool(_numberOfThreads);
        
        // Start threads
        for(int i = 0; i < _numberOfThreads; i++){
            MinInArrayRangeTask task = new MinInArrayRangeTask(_array, _ranges[i].GetLowerRange(), _ranges[i].GetUpperRange());
            Future<Integer> future = executor.submit(task);
            futures.add(future);
        }

        // Process the return values of the tasks
        for (int i = 0; i < futures.size(); i++) {
            try {
                int min = futures.get(i).get();
                _threadMins.add(min);
            } catch (InterruptedException | ExecutionException e) {
                System.out.println("An error occurred while retrieving the result: " + e.getMessage());
            }
        }

        // Find global min
        for(int i = 0; i < _threadMins.size(); i++){
            if(_array[_threadMins.get(i)] < _array[_minIndex]){
                _minIndex = _threadMins.get(i);
            }
        }

        executor.shutdown();
        while (!executor.isTerminated()){} // Wait for all threads to finish
    }

    public void FindMaxIndexInArray(){
        List<Integer> _threadMaxs = new ArrayList<Integer>();
        List<Future<Integer>> futures = new ArrayList<>();
        _maxIndex = 0;

        ExecutorService executor = Executors.newFixedThreadPool(_numberOfThreads);
        
        // Start threads
        for(int i = 0; i < _numberOfThreads; i++){
            MaxInArrayRangeTask task = new MaxInArrayRangeTask(_array, _ranges[i].GetLowerRange(), _ranges[i].GetUpperRange());
            Future<Integer> future = executor.submit(task);
            futures.add(future);
        }

        // Process the return values of the tasks
        for (int i = 0; i < futures.size(); i++) {
            try {
                int max = futures.get(i).get();
                _threadMaxs.add(max);
            } catch (InterruptedException | ExecutionException e) {
                System.out.println("An error occurred while retrieving the result: " + e.getMessage());
            }
        }

        // Find global max
        for(int i = 0; i < _threadMaxs.size(); i++){
            if(_array[_threadMaxs.get(i)] > _array[_maxIndex]){
                _maxIndex = _threadMaxs.get(i);
            }
        }

        executor.shutdown();
        while (!executor.isTerminated()){} // Wait for all threads to finish
    }
    
    /**
     * DisplayRanges function prints the lower and upper range values of each range in the array.
     * 
     * @remarks This function assumes that the _ranges array has been properly initialized and contains valid range objects.
     */
    public void DisplayRanges(){
        for(int i = 0; i < _ranges.length; i++){
            System.out.println("[" + String.valueOf(_ranges[i].GetLowerRange()) + ", " + String.valueOf(_ranges[i].GetUpperRange()) + ")");
        }
    }

    /**
     * @brief Returns the sum of the array. Calling this assumes it was already calculated.
     */
    public Integer GetArraySum(){ return _sum; }

    public Double GetArrayProd(){ return _prod; }

    public Integer GetMinIndex(){ return _minIndex; }

    public Integer GetMaxIndex(){ return _maxIndex; }

    /**
     * CalculateRanges function divides the array into ranges based on the number of threads.
     * 
     * @remarks This function assumes that _arrayLength and _numberOfThreads have valid values.
     */
    private void CalculateRanges(){
        _ranges = new Range[_numberOfThreads];

        // Calculate the length of each part of the splitting.
        double quotient = (float) _arrayLength / _numberOfThreads; // divide the number into n parts
        int part_size = (int)Math.floor(quotient); // round the result to the nearest integer

        int remainder = _arrayLength % part_size; // calculate the remaining amount after division

        int currentLowerRange = 1;
        for(int i = 0; i < _numberOfThreads; i++){
            if(remainder != 0){
                _ranges[i] = new Range(currentLowerRange - 1, currentLowerRange + part_size);
                remainder--;
            }else{
                _ranges[i] = new Range(currentLowerRange - 1, currentLowerRange + part_size - 1);
            }
            currentLowerRange = _ranges[i].GetUpperRange() + 1;
        }
    }

    /**
     * GenerateArrayTask is a task that generates random values and assigns them to a portion of an array.
     * 
     * @remarks This class is designed to be used with the Runnable interface.
     */
    private static class GenerateArrayTask implements Runnable {
        private int[] _array;
        private int _startIndex;
        private int _endIndex;
        private int _valueLowerLimit;
        private int _valueUpperLimit;

        /**
         * Constructs a new GenerateArrayTask object.
         * 
         * @param array The array to populate with random values.
         * @param startIndex The starting index (inclusive) of the array portion to populate.
         * @param endIndex The ending index (exclusive) of the array portion to populate.
         * @param valueLowerLimit The lower limit (inclusive) for the random values.
         * @param valueUpperLimit The upper limit (inclusive) for the random values.
         */
        public GenerateArrayTask(int[] array, int startIndex, int endIndex, int valueLowerLimit, int valueUpperLimit) {
            this._array = array;
            this._startIndex = startIndex;
            this._endIndex = endIndex;
            this._valueLowerLimit = valueLowerLimit;
            this._valueUpperLimit = valueUpperLimit;
        }

        /**
         * Executes the task of generating random values and assigning them to the array portion.
         */
        @Override
        public void run() {
            for (int i = _startIndex; i < _endIndex; i++) {
                double randomNum = ((Math.random() * (_valueUpperLimit - _valueUpperLimit + 1)) + _valueLowerLimit) * 100;
                _array[i] = (int) Math.floor(randomNum);
            }
        }
    }

    /**
     * SumArrayRangeTask is a task that calculates the sum of a range of elements in an array.
     * 
     * @remarks This class is designed to be used with the Callable interface.
     */
    private static class SumArrayRangeTask implements Callable<Integer> {
        private int[] _array;
        private int _startIndex;
        private int _endIndex;

        /**
         * Constructs a new SumArrayRangeTask object.
         * 
         * @param array The array from which to calculate the sum.
         * @param startIndex The starting index (inclusive) of the range to calculate the sum.
         * @param endIndex The ending index (exclusive) of the range to calculate the sum.
         */
        public SumArrayRangeTask(int[] array, int startIndex, int endIndex) {
            this._array = array;
            this._startIndex = startIndex;
            this._endIndex = endIndex;
        }

        /**
         * Executes the task of calculating the sum of the range of elements in the array.
         * 
         * @returns The sum of the range of elements.
         */
        @Override
        public Integer call() {
            int _threadSum = 0;

            for (int i = _startIndex; i < _endIndex; i++) {
                _threadSum += _array[i];
            }

            return _threadSum;
        }
    }

    /**
     * A task that calculates the product of array elements within a specified range, with value mapping.
     * The mapping function converts integer values to double values within a given range.
     * The product is computed by multiplying the mapped values together.
     *
     * @param array The array containing the elements to be multiplied.
     * @param startIndex The starting index (inclusive) of the range.
     * @param endIndex The ending index (exclusive) of the range.
     * @param valueLowerLimit The lower limit (inclusive) for the integer value mapping.
     * @param valueUpperLimit The upper limit (inclusive) for the integer value mapping.
     * @return The product of the mapped array elements within the specified range.
     */
    private static class ProdArrayRangeTask implements Callable<Double> {
        private int[] _array;
        private int _startIndex;
        private int _endIndex;
        private int _valueLowerLimit;
        private int _valueUpperLimit;

        /**
         * Constructs a new ProdArrayRangeTask object.
         *
         * @param array The array containing the elements to be multiplied.
         * @param startIndex The starting index (inclusive) of the range.
         * @param endIndex The ending index (exclusive) of the range.
         * @param valueLowerLimit The lower limit (inclusive) for the integer value mapping.
         * @param valueUpperLimit The upper limit (inclusive) for the integer value mapping.
         */
        public ProdArrayRangeTask(int[] array, int startIndex, int endIndex, int valueLowerLimit, int valueUpperLimit) {
            this._array = array;
            this._startIndex = startIndex;
            this._endIndex = endIndex;
            this._valueLowerLimit = valueLowerLimit;
            this._valueUpperLimit = valueUpperLimit;
        }

        /**
         * Computes the product of the mapped array elements within the specified range.
         *
         * @return The product of the mapped array elements within the specified range.
         */
        @Override
        public Double call() {
            Double _threadProd = 1.0;

            for (int i = _startIndex; i < _endIndex; i++) {
                if(_threadProd > 1){
                    _threadProd *= 1/MapIntToDouble(_array[i], _valueLowerLimit, _valueUpperLimit, 1.0, 1.1);
                }else{
                    _threadProd *= MapIntToDouble(_array[i], _valueLowerLimit, _valueUpperLimit, 1.0, 1.1);
                }
            }

            return _threadProd;
        }

        /**
         * Maps an integer value from a given range to a corresponding double value in another range.
         *
         * @param value The integer value to be mapped.
         * @param i_min The minimum value of the input integer range.
         * @param i_max The maximum value of the input integer range.
         * @param d_min The minimum value of the output double range.
         * @param d_max The maximum value of the output double range.
         * @return The double value mapped from the input integer value to the output range.
         */
        private Double MapIntToDouble(int value, int i_min, int i_max, double d_min, double d_max){
            return (double)(value - i_min) * (double)(d_max - d_min) / (double)(i_max - i_min) + d_min;
        }
    }

    /**
     * A task that finds the index of the minimum element within a specified range of an array.
     *
     * @param array The array to search for the minimum element.
     * @param startIndex The starting index (inclusive) of the range.
     * @param endIndex The ending index (exclusive) of the range.
     * @return The index of the minimum element within the specified range.
     */
    private static class MinInArrayRangeTask implements Callable<Integer> {
        private int[] _array;
        private int _startIndex;
        private int _endIndex;

        /**
         * Constructs a new MinInArrayRangeTask object.
         *
         * @param array The array to search for the minimum element.
         * @param startIndex The starting index (inclusive) of the range.
         * @param endIndex The ending index (exclusive) of the range.
         */
        public MinInArrayRangeTask(int[] array, int startIndex, int endIndex) {
            this._array = array;
            this._startIndex = startIndex;
            this._endIndex = endIndex;
        }

        /**
         * Finds the index of the minimum element within the specified range of the array.
         *
         * @return The index of the minimum element within the specified range.
         */
        @Override
        public Integer call() {
            int _minIndex = _startIndex;

            for (int i = _startIndex + 1; i < _endIndex; i++) {
                if(_array[i] < _array[_minIndex]){
                    _minIndex = i;
                }
            }

            return _minIndex;
        }
    }

    /**
     * A task that finds the index of the maximum element within a specified range of an array.
     *
     * @param array The array to search for the maximum element.
     * @param startIndex The starting index (inclusive) of the range.
     * @param endIndex The ending index (exclusive) of the range.
     * @return The index of the maximum element within the specified range.
     */
    private static class MaxInArrayRangeTask implements Callable<Integer> {
        private int[] _array;
        private int _startIndex;
        private int _endIndex;

        /**
         * Constructs a new MaxInArrayRangeTask object.
         *
         * @param array The array to search for the maximum element.
         * @param startIndex The starting index (inclusive) of the range.
         * @param endIndex The ending index (exclusive) of the range.
         */
        public MaxInArrayRangeTask(int[] array, int startIndex, int endIndex) {
            this._array = array;
            this._startIndex = startIndex;
            this._endIndex = endIndex;
        }

        /**
         * Finds the index of the maximum element within the specified range of the array.
         *
         * @return The index of the maximum element within the specified range.
         */
        @Override
        public Integer call() {
            int _maxIndex = _startIndex;

            for (int i = _startIndex + 1; i < _endIndex; i++) {
                if(_array[i] > _array[_maxIndex]){
                    _maxIndex = i;
                }
            }

            return _maxIndex;
        }
    }
}