#include "SP500.hxx"
#include "data.hxx"
#include <cppuhelper/supportsservice.hxx>
#include <rtl/ustring.hxx>

using rtl::OUString;
using namespace com::sun::star::uno;

// This is the service name an Add-On has to implement
#define BASE_SERVICE_NAME "com.sun.star.sheet.AddIn"
#define SERVICE_NAME "com.sun.star.sheet.addin.SP500Addin"

// Helper functions for the implementation of UNO component interfaces.
OUString SP500AddinImpl_getImplementationName()
throw (RuntimeException)
{
    return OUString ( IMPLEMENTATION_NAME );
}

Sequence< OUString > SAL_CALL SP500AddinImpl_getSupportedServiceNames()
throw (RuntimeException)
{
    Sequence < OUString > aRet(2);
    OUString* pArray = aRet.getArray();
    pArray[0] =  OUString ( BASE_SERVICE_NAME );
    pArray[1] =  OUString ( SERVICE_NAME );
    return aRet;
}

Reference< XInterface > SAL_CALL SP500AddinImpl_createInstance( const Reference< XComponentContext > & rContext)
    throw( Exception )
{
    return (cppu::OWeakObject*) new SP500AddinImpl();
}

OUString SP500AddinImpl::getServiceName()
{
    return SERVICE_NAME;
}

// Implementation of the recommended/mandatory interfaces of a UNO component.
// XServiceInfo
OUString SAL_CALL SP500AddinImpl::getImplementationName()
    throw (RuntimeException)
{
    return SP500AddinImpl_getImplementationName();
}

sal_Bool SAL_CALL SP500AddinImpl::supportsService( const OUString& rServiceName )
    throw (RuntimeException)
{
    //return cppu::supportsService(this, rServiceName);
    printf("DEBUG>>> supportService(%s)\n", OUStringToOString( rServiceName, RTL_TEXTENCODING_ASCII_US ).getStr()); fflush(stdout);
    return ( rServiceName == BASE_SERVICE_NAME || rServiceName == SERVICE_NAME );
}

Sequence< OUString > SAL_CALL SP500AddinImpl::getSupportedServiceNames(  )
    throw (RuntimeException)
{
    printf("DEBUG>>> inside getSupportedServiceNames()\n"); fflush(stdout);
    return SP500AddinImpl_getSupportedServiceNames();
}


const OUString SP500AddinImpl::aFunctionNames[NUMFUNCTIONS] = {
    "getTicker",
    "getName"
};

const OUString SP500AddinImpl::aDisplayFunctionNames[NUMFUNCTIONS] = {
    "getticker",
    "getcompname"
};

const OUString SP500AddinImpl::aDescriptions[NUMFUNCTIONS] = {
    "Gets SP500 ticker of given index",
    "Gets company name of given ticker"
};

const OUString SP500AddinImpl::aFirstArgumentNames[NUMFUNCTIONS] = {
    "Index",
    "Ticker"
};

const OUString SP500AddinImpl::aFirstArgumentDescriptions[NUMFUNCTIONS] = {
    "Index of SP500 ticker to be returned",
    "Ticker whose company name is to be returned"
};

sal_Int32 SP500AddinImpl::getFunctionID( const OUString aProgrammaticFunctionName ) const
{
    for ( sal_Int32 nIdx = 0; nIdx < nNumFunctions; ++nIdx )
        if ( aProgrammaticFunctionName == aFunctionNames[nIdx] )
            return nIdx;
    return -1;
}

OUString SP500AddinImpl::getTicker( sal_Int32 nIdx )
{
    if ( nIdx < 0 || nIdx >= aTickers.size())
        return "Bad Index";
    return aTickers[nIdx];
}

OUString SP500AddinImpl::getName( const OUString& aTicker )
{
    auto it = aTickerToName.find(aTicker);
    if ( it == aTickerToName.end() )
        return "Bad Ticker";
    return it->second;
}


OUString SP500AddinImpl::getProgrammaticFuntionName( const OUString& aDisplayName )
{
    printf("DEBUG >>> getProgrammaticFuntionName(%s)\n", OUStringToOString( aDisplayName, RTL_TEXTENCODING_ASCII_US ).getStr()); fflush(stdout);
    for ( sal_Int32 nIdx = 0; nIdx < nNumFunctions; ++nIdx )
        if ( aDisplayName == aDisplayFunctionNames[nIdx] )
            return aFunctionNames[nIdx];
    return "";
}

OUString SP500AddinImpl::getDisplayFunctionName( const OUString& aProgrammaticName )
{
    printf("DEBUG >>> getDisplayFunctionName(%s)\n", OUStringToOString( aProgrammaticName, RTL_TEXTENCODING_ASCII_US ).getStr()); fflush(stdout);
    sal_Int32 nFIdx = getFunctionID( aProgrammaticName );
    return ( nFIdx == -1 ) ? "" : aDisplayFunctionNames[nFIdx];
}

OUString SP500AddinImpl::getFunctionDescription( const OUString& aProgrammaticName )
{
    sal_Int32 nFIdx = getFunctionID( aProgrammaticName );
    return ( nFIdx == -1 ) ? "" : aDescriptions[nFIdx];
}

OUString SP500AddinImpl::getDisplayArgumentName( const OUString& aProgrammaticFunctionName, sal_Int32 nArgument )
{
    sal_Int32 nFIdx = getFunctionID( aProgrammaticFunctionName );
    return ( nFIdx == -1 || nArgument != 0 ) ? "" : aFirstArgumentNames[nFIdx];
}

OUString SP500AddinImpl::getArgumentDescription( const OUString& aProgrammaticFunctionName, sal_Int32 nArgument )
{
    sal_Int32 nFIdx = getFunctionID( aProgrammaticFunctionName );
    return ( nFIdx == -1 || nArgument != 0 ) ? "" : aFirstArgumentDescriptions[nFIdx];
}

OUString SP500AddinImpl::getProgrammaticCategoryName( const OUString& aProgrammaticFunctionName )
{
    printf("DEBUG>>> inside getProgrammaticCategoryName()\n");fflush(stdout);
    return "Add-In";
}

OUString SP500AddinImpl::getDisplayCategoryName( const OUString& aProgrammaticFunctionName )
{
    printf("DEBUG>>> inside getDisplayCategoryName()\n");fflush(stdout);
    return "Add-In";
}
