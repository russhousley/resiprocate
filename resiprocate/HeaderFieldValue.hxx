#ifndef HeaderFieldValue_hxx
#define HeaderFieldValue_hxx

#include <sipstack/SubComponentList.hxx>
#include <sipstack/ParseException.hxx>


namespace Vocal2
{

class ParserCategory;
class UnknownSubComponent;

class HeaderFieldValue
{
   public:
      HeaderFieldValue();
      HeaderFieldValue(const char* field, unsigned int fieldLength);
      HeaderFieldValue(const HeaderFieldValue& hfv);
      HeaderFieldValue(ParserCategory* parserCategory);

      ~HeaderFieldValue();

      HeaderFieldValue* clone() const;
      SubComponentList& getSubComponents();
      SubComponentList& getUnknownSubComponents();
      bool isParsed() const;

      bool exists(const Data& subcomponent);
      bool exists(const SubComponent::Type type);
      
      UnknownSubComponent* get(const Data& type);
      
      HeaderFieldValue* next;

      ParserCategory& getParserCategory()
      {
         return *mParserCategory;
      }
      
      friend std::ostream& operator<<(std::ostream&, HeaderFieldValue&);

      ParserCategory* mParserCategory;
   private:
      const char* mField;
      const unsigned int mFieldLength;
      SubComponentList mSubComponentList;
      SubComponentList mUnknownSubComponentList;
      bool mMine;
};


std::ostream& operator<<(std::ostream& stream, 
			 HeaderFieldValue& hList);


}



#endif
