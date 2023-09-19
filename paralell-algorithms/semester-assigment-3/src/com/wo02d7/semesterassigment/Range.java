package com.wo02d7.semesterassigment;

public class Range {
    private int _lowerRange;
    private int _upperRange;

    public Range(int lowerRange, int upperRange){
        this._lowerRange = lowerRange;
        this._upperRange = upperRange;
    }
    
    public int GetLowerRange(){ return _lowerRange; }
    public int GetUpperRange(){ return _upperRange; }
}
