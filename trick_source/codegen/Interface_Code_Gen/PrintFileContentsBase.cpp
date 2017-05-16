
#include <sys/stat.h>
#include <libgen.h>
#include <string.h>
#include <iomanip>
#include <sstream>

#include "llvm/Support/CommandLine.h"

#include "PrintFileContentsBase.hh"
#include "FieldDescription.hh"
#include "ClassValues.hh"
#include "EnumValues.hh"

extern llvm::cl::opt< bool > global_compat15 ;

PrintFileContentsBase::PrintFileContentsBase() {}

// provide empty default implementation of these routines.
void PrintFileContentsBase::printClassMapHeader(std::ostream & ostream, std::string function_name ) {}
void PrintFileContentsBase::printClassMap(std::ostream & ostream, ClassValues * cv) {}
void PrintFileContentsBase::printClassMapFooter(std::ostream & ostream) {}

void PrintFileContentsBase::printEnumMapHeader(std::ostream & ostream, std::string function_name ) {}
void PrintFileContentsBase::printEnumMap(std::ostream & ostream, EnumValues * ev) {}
void PrintFileContentsBase::printEnumMapFooter(std::ostream & ostream) {}

void PrintFileContentsBase::print_units_map(std::ostream & ostream, ClassValues * cv ) {
    const std::string name = cv->getFullyQualifiedMangledTypeName("__");
    ostream << "struct UnitsMap" << name << " {\n" ;

    auto fields = getPrintableFields(*cv);
    if (fields.size()) {
        ostream << "    UnitsMap" << name << "() {\n"
                << "        Trick::UnitsMap* units_map_ptr = Trick::UnitsMap::units_map();\n" ;
        for (auto& field : fields) {
            ostream << "        units_map_ptr->add_param(\"" ;
            cv->printContainerClasses(ostream, "__");
            ostream << cv->getName() << "_" << field->getName() << "\", \"" << field->getUnits() << "\") ;\n" ;
        }
        ostream << "    }\n" ;
    }

    ostream << "} um" << name << ";\n" ;
}

/* Utility routines for printing */
void PrintFileContentsBase::print_open_extern_c(std::ostream & ostream) {
    ostream << "extern \"C\" {\n\n" ;
}

void PrintFileContentsBase::print_close_extern_c(std::ostream & ostream) {
    ostream << "\n} //extern \"C\"\n\n" ;
}

/* internal function determines if a particular field is printable based
   on access to the field and the presense of init_attr friends.
*/
bool PrintFileContentsBase::determinePrintAttr( ClassValues * c , FieldDescription * fdes ) {
    if ( !fdes->getTypeName().compare("void") or !fdes->getChkpntIO() or !fdes->getEnumString().compare("TRICK_VOID")) {
        return false;
    }
    if ( fdes->getAccess() == clang::AS_public or (!fdes->isStatic() and !global_compat15 and !c->isCompat15())) {
        return true;
    }
    return c->getHasInitAttrFriend() && ( !fdes->isInherited() || fdes->getAccess() == clang::AS_protected ) ;
}

std::vector<FieldDescription*> PrintFileContentsBase::getPrintableFields(ClassValues& classValues) {
    std::vector<FieldDescription*> results;
    for (auto& field : classValues.getFieldDescriptions()) {
        if (determinePrintAttr(&classValues, field) and field->getUnits().compare("1")) {
            results.push_back(field);
        }
    }
    return results;
}

