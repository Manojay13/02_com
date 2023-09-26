#pragma once

class IMultiplication :public IUnkown
{
    public:
        virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int*)=0;

};

class IDivision :public IUnknown
{
    public:
        virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int*)=0;
};

// CLSID_MultiplicationDivision {91C2E08B-5BB8-4453-AEB6-1C2D8B03BF7B}
const CLSID CLSID_MultiplicationDivision ={
0x91c2e08b, 0x5bb8, 0x4453, 0xae, 0xb6, 0x1c, 0x2d, 0x8b, 0x3, 0xbf, 0x7};

// IID of IMultiplication Interface{DBDC907E-07AC-45CB-9FC5-10360A5E1458}
const IID IID_IMultiplication={ 
0xdbdc907e, 0x7ac, 0x45cb, 0x9f, 0xc5, 0x10, 0x36, 0xa, 0x5e, 0x14, 0x58};
