package com.wo02d7.semesterassigment;

public class Main{
    public static void main(String[] args){
        long programStartTime = System.currentTimeMillis();

        SpecializedArray specializedArray = null;

        if(args.length != 4){
            System.out.println("Invalid arguments!");
        }

        try{
            int tempArrayLength = Integer.parseInt(args[0]);
            int tempValueLowerLimit = Integer.parseInt(args[1]);
            int tempValueUpperLimit = Integer.parseInt(args[2]);
            int tempNumberOfThreads = Integer.parseInt(args[3]);

            specializedArray = new SpecializedArray(tempArrayLength, tempValueLowerLimit, tempValueUpperLimit, tempNumberOfThreads);
            System.out.println("Specialized array successfully created!\n");
        }catch(Exception e){
            System.out.println("Given argument(s) are not valid int");
            System.exit(1);
        }
        long startTime = System.currentTimeMillis();
        System.out.println("Generating array... ");
        specializedArray.GenerateArray();
        System.out.println("Array generated!");
        long endTime = System.currentTimeMillis();
        long executionTime = endTime - startTime;
        System.out.println("Array generation time: " + executionTime + " milliseconds\n");

        startTime = System.currentTimeMillis();
        System.out.println("Summing array... ");
        specializedArray.SumArray();
        System.out.println("Array summed!");
        System.out.println("Array sum: " + String.valueOf(specializedArray.GetArraySum()) + "");
        endTime = System.currentTimeMillis();
        executionTime = endTime - startTime;
        System.out.println("Array sum time: " + executionTime + " milliseconds\n");

        startTime = System.currentTimeMillis();
        System.out.println("Prodding array... ");
        specializedArray.ProdArray();
        System.out.println("Array prodded!");
        System.out.println("Array prod: " + String.valueOf(specializedArray.GetArrayProd()) + "");
        endTime = System.currentTimeMillis();
        executionTime = endTime - startTime;
        System.out.println("Array prod time: " + executionTime + " milliseconds\n");

        startTime = System.currentTimeMillis();
        System.out.println("Finding min index in array... ");
        specializedArray.FindMinIndexInArray();
        System.out.println("Min index found!");
        System.out.println("Min index: " + String.valueOf(specializedArray.GetMinIndex()) + "");
        endTime = System.currentTimeMillis();
        executionTime = endTime - startTime;
        System.out.println("Finding min time: " + executionTime + " milliseconds\n");

        startTime = System.currentTimeMillis();
        System.out.println("Finding max index in array... ");
        specializedArray.FindMaxIndexInArray();
        System.out.println("Max index found!");
        System.out.println("Max index: " + String.valueOf(specializedArray.GetMaxIndex()) + "");
        endTime = System.currentTimeMillis();
        executionTime = endTime - startTime;
        System.out.println("Finding min time: " + executionTime + " milliseconds\n");

        long programEndTime = System.currentTimeMillis();
        long programExecutionTime = programEndTime - programStartTime;
        System.out.println("Program time: " + programExecutionTime + " milliseconds\n");
    }
}