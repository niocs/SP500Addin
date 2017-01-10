#ifndef COM_SUN_STAR_SHEET_ADDIN_SP500_HXX
#define COM_SUN_STAR_SHEET_ADDIN_SP500_HXX

#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/sheet/addin/XSP500Addin.hpp>
#include <com/sun/star/sheet/XAddIn.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XServiceName.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <cppuhelper/implbase4.hxx>

#define IMPLEMENTATION_NAME "com.sun.star.sheet.addin.SP500AddinImpl"
#define NUMFUNCTIONS 2

class SP500AddinImpl : public cppu::WeakImplHelper4
<
    com::sun::star::sheet::addin::XSP500Addin,
    com::sun::star::sheet::XAddIn,
    com::sun::star::lang::XServiceName,
    com::sun::star::lang::XServiceInfo
>
{
private:
    static const sal_Int32 nNumFunctions = NUMFUNCTIONS;
    static const ::rtl::OUString aFunctionNames[NUMFUNCTIONS];
    static const ::rtl::OUString aDisplayFunctionNames[NUMFUNCTIONS];
    static const ::rtl::OUString aDescriptions[NUMFUNCTIONS];
    static const ::rtl::OUString aFirstArgumentNames[NUMFUNCTIONS];
    static const ::rtl::OUString aFirstArgumentDescriptions[NUMFUNCTIONS];

    com::sun::star::lang::Locale aFuncLocale;
    
public:

    SP500AddinImpl()
    {
        printf("DEBUG>>> Created an instance of SP500AddinImpl %p\n", this); fflush(stdout);
    }

    // XSP500Addin
    rtl::OUString getTicker( sal_Int32 nIdx );
    rtl::OUString getName( const rtl::OUString& aTicker );

    // XAddIn
    rtl::OUString getProgrammaticFuntionName( const rtl::OUString& aDisplayName );
    rtl::OUString getDisplayFunctionName( const rtl::OUString& aProgrammaticName );
    rtl::OUString getFunctionDescription( const rtl::OUString& aProgrammaticName );
    rtl::OUString getDisplayArgumentName( const rtl::OUString& aProgrammaticFunctionName, sal_Int32 nArgument );
    rtl::OUString getArgumentDescription( const rtl::OUString& aProgrammaticFunctionName, sal_Int32 nArgument );
    rtl::OUString getProgrammaticCategoryName( const rtl::OUString& aProgrammaticFunctionName );
    rtl::OUString getDisplayCategoryName( const rtl::OUString& aProgrammaticFunctionName );
    //  XLocalizable
    void setLocale( const com::sun::star::lang::Locale& aLocale ) { aFuncLocale = aLocale; }
    com::sun::star::lang::Locale getLocale() { return aFuncLocale; }

    // XServiceInfo methods
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw (::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& aServiceName )
        throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw (::com::sun::star::uno::RuntimeException);

    ::rtl::OUString getServiceName();

private:

    sal_Int32 getFunctionID( const rtl::OUString aProgrammaticFunctionName ) const;
    
};

::rtl::OUString SP500AddinImpl_getImplementationName()
    throw ( ::com::sun::star::uno::RuntimeException );

sal_Bool SAL_CALL SP500AddinImpl_supportsService( const ::rtl::OUString& ServiceName )
    throw ( ::com::sun::star::uno::RuntimeException );

::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL SP500AddinImpl_getSupportedServiceNames()
    throw ( ::com::sun::star::uno::RuntimeException );

::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
SAL_CALL SP500AddinImpl_createInstance( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > & rContext)
    throw ( ::com::sun::star::uno::Exception );
    

#endif
