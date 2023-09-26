#include<windows.h>
#include"ContainmentInnerComponetWithRegFile.h"

class CMultiplicationDivision :public Imultiplication,IDivision
{
    private:
        long m_cRef;
    public:
    CMultiplicationDivision(void);
    ~CMultiplicationDivision(void);


    //IUnknown Specific Declarations(inherited)
    HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stacall AddRef(void);
    ULONG __stdcall Release(void);

    //IMultiplication specific method declarations(Inherited)
    HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);

    //IDivision specific method Declaration(Inherited)
    HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);
};


class CMultiplicationDivisionClassFactory :public IClassFactory
{
    private:
        long m_cRef;
    public:
        CMultiplicationDivisionClassFactory(void);
        ~CMultiplicationDivisionClassFactory(void);

        //IUnknown Specific Method Declaration
        HRESULT __stdcall QueryInterface(REFIID, void**) ;
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);

        //IClassFactory specific method declarations(Inherited)
        HRESULT __stdcall CreateInstance(IUnknown *,REFIID, void **);

        HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0;//number of active components
long glNumberOfServerLocks = 0;//numbers of locks on this dll

//Dllmain
BOOL WINAPI DllMain(HInstance hDll,DWORD dwReason, LPVOID Reserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    
    case DLL_PROCESS_DETACH:
        break;
    }

    return(TRUE);
}

//Implementation of CMUltiplicationDivision's Constructor method
CMultiplicationDivision::CMultiplicationDivision(void){
    m_cRef = 1;//hardcoded intialisation to anticipate possible failure of QueryInterface()
    InterlockedIncreamnet(&glNumberOfActiveComponents);//increment global counter
}

//Implementation of CMultiplicationDivision destructor method
CMultiplicationDivision::~CMultiplicationDivision(void)
{
    InterlockedDecrement(&glNumberOfActiveComponents);//decreamnet global counter
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
    if(riid == IID_IUnknown)
        *ppv = static_cast<IMultiplication *>(this);
    else if (riid == IID_IMultiplication)
        *ppv = static_cast<IMultiplication *>(this);
    else if(riid == IID_IDivision)
        *ppv = static_cast<IID_IDivision *> (this);
    else
    {
        *ppv = NULL;
        return(E_NOINTERFACE);
    }

    reinterpret_cast<IUnknown *>(*ppv)->AddRef();

    return(S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
    InterlockedDecrement(&m_cRef);
    return(m_cRef);
}

ULONG CMultiplicationDivision::Release(void)
{
    InterlockedDecrement(&m_cRef);

    if(m_cRef==0)
    {
        delete(this);
        return(0);
    }

    return(m_cRef);
}

//Implementation of Imultiplication's methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
    *pMultiplication = num1*num2;
    return(S_OK);
}

//Implementation of IDivision's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
    *pDivision = num1/num2;
    return(S_OK);
}


//Implementation of CMultiplicatioDivisionClassfactory's constructor method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
    m_cRef =1;//hardcoded initialization of anticipate posible failure of QueryInterface()
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
    //code
}


//Implementation of CMultiplicationClassFactory's IClassFactory's IUnknown's Methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
    if(riid == IID_IUnknown)
        *ppv = static_cast<IClassFactory *>(this);
    else if(riid == IID_IClassFactory)
        *ppv = static_cast<IClassFactory *>(this);
    else
    {
        *ppv = NULL;
        return(E_NOINTERFACE);
    }
    reinterpret_cast<IUknown *>(*ppv)->AddRef();

    return(S_OK);
}


ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return(m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
    InterlockedDecrement(&m_cRef);

    if(m_cRef==0)
    {
        delete(this);
        return(0);
    }

    return(m_cRef);
}

//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's Methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void *ppv)
{
    CMultiplicationDivision *pCMultiplicationDivision = NULL;
    HRESULT hr;

    if(pUnkOuter != NULL)
    return(CLASS_E_NOAGGREGATION);

    //create instance of component  i.e.of CMultiplicationDivision
    class pCMultiplicationDivision = new CMultiplicationDivision;

    if(pCMultiplicationDivision == NULL)
        return(E_OUTOFMEMORY);
    
    //get requested interface
    hr = pCMultiplicationDivision->QueryInterface(riid, ppv);

    pCMultiplicationDivision->Release();//anticipate possible failure of QueryInterface

    return(hr);
}


HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
    if(fLock)
        InterlockedIncrement(&glNumberOfServerLocks);
    else
        InterlockedDecrement(&glNumberOfServerLocks);

    return(S_OK);
}