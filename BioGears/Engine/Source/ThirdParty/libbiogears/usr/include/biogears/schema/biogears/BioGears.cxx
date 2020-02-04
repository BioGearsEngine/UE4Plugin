// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "BioGears.hxx"

namespace mil
{
  namespace tatrc
  {
    namespace physiology
    {
      namespace datamodel
      {
        // enumBioGearsAirwayMode
        // 

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode ()
        : ::xml_schema::string ()
        {
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (value v)
        : ::xml_schema::string (_xsd_enumBioGearsAirwayMode_literals_[v])
        {
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const char* v)
        : ::xml_schema::string (v)
        {
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const ::std::string& v)
        : ::xml_schema::string (v)
        {
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const ::xml_schema::string& v)
        : ::xml_schema::string (v)
        {
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const enumBioGearsAirwayMode& v,
                                ::xml_schema::flags f,
                                ::xml_schema::container* c)
        : ::xml_schema::string (v, f, c)
        {
        }

        enumBioGearsAirwayMode& enumBioGearsAirwayMode::
        operator= (value v)
        {
          static_cast< ::xml_schema::string& > (*this) = 
          ::xml_schema::string (_xsd_enumBioGearsAirwayMode_literals_[v]);

          return *this;
        }


        // BioGearsStateData
        // 

        const BioGearsStateData::AirwayMode_type& BioGearsStateData::
        AirwayMode () const
        {
          return this->AirwayMode_.get ();
        }

        BioGearsStateData::AirwayMode_type& BioGearsStateData::
        AirwayMode ()
        {
          return this->AirwayMode_.get ();
        }

        void BioGearsStateData::
        AirwayMode (const AirwayMode_type& x)
        {
          this->AirwayMode_.set (x);
        }

        void BioGearsStateData::
        AirwayMode (::std::unique_ptr< AirwayMode_type > x)
        {
          this->AirwayMode_.set (std::move (x));
        }

        const BioGearsStateData::Intubation_type& BioGearsStateData::
        Intubation () const
        {
          return this->Intubation_.get ();
        }

        BioGearsStateData::Intubation_type& BioGearsStateData::
        Intubation ()
        {
          return this->Intubation_.get ();
        }

        void BioGearsStateData::
        Intubation (const Intubation_type& x)
        {
          this->Intubation_.set (x);
        }

        void BioGearsStateData::
        Intubation (::std::unique_ptr< Intubation_type > x)
        {
          this->Intubation_.set (std::move (x));
        }
      }
    }
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

#include <xsd/cxx/tree/type-factory-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_factory_plate< 0, char >
  type_factory_plate_init;
}

namespace mil
{
  namespace tatrc
  {
    namespace physiology
    {
      namespace datamodel
      {
        // enumBioGearsAirwayMode
        //

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const ::xercesc::DOMElement& e,
                                ::xml_schema::flags f,
                                ::xml_schema::container* c)
        : ::xml_schema::string (e, f, c)
        {
          _xsd_enumBioGearsAirwayMode_convert ();
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const ::xercesc::DOMAttr& a,
                                ::xml_schema::flags f,
                                ::xml_schema::container* c)
        : ::xml_schema::string (a, f, c)
        {
          _xsd_enumBioGearsAirwayMode_convert ();
        }

        enumBioGearsAirwayMode::
        enumBioGearsAirwayMode (const ::std::string& s,
                                const ::xercesc::DOMElement* e,
                                ::xml_schema::flags f,
                                ::xml_schema::container* c)
        : ::xml_schema::string (s, e, f, c)
        {
          _xsd_enumBioGearsAirwayMode_convert ();
        }

        enumBioGearsAirwayMode* enumBioGearsAirwayMode::
        _clone (::xml_schema::flags f,
                ::xml_schema::container* c) const
        {
          return new class enumBioGearsAirwayMode (*this, f, c);
        }

        enumBioGearsAirwayMode::value enumBioGearsAirwayMode::
        _xsd_enumBioGearsAirwayMode_convert () const
        {
          ::xsd::cxx::tree::enum_comparator< char > c (_xsd_enumBioGearsAirwayMode_literals_);
          const value* i (::std::lower_bound (
                            _xsd_enumBioGearsAirwayMode_indexes_,
                            _xsd_enumBioGearsAirwayMode_indexes_ + 4,
                            *this,
                            c));

          if (i == _xsd_enumBioGearsAirwayMode_indexes_ + 4 || _xsd_enumBioGearsAirwayMode_literals_[*i] != *this)
          {
            throw ::xsd::cxx::tree::unexpected_enumerator < char > (*this);
          }

          return *i;
        }

        const char* const enumBioGearsAirwayMode::
        _xsd_enumBioGearsAirwayMode_literals_[4] =
        {
          "Free",
          "AnesthesiaMachine",
          "Inhaler",
          "MechanicalVentilator"
        };

        const enumBioGearsAirwayMode::value enumBioGearsAirwayMode::
        _xsd_enumBioGearsAirwayMode_indexes_[4] =
        {
          ::mil::tatrc::physiology::datamodel::enumBioGearsAirwayMode::AnesthesiaMachine,
          ::mil::tatrc::physiology::datamodel::enumBioGearsAirwayMode::Free,
          ::mil::tatrc::physiology::datamodel::enumBioGearsAirwayMode::Inhaler,
          ::mil::tatrc::physiology::datamodel::enumBioGearsAirwayMode::MechanicalVentilator
        };

        static
        const ::xsd::cxx::tree::type_factory_initializer< 0, char, enumBioGearsAirwayMode >
        _xsd_enumBioGearsAirwayMode_type_factory_init (
          "enumBioGearsAirwayMode",
          "uri:/mil/tatrc/physiology/datamodel");

        // BioGearsStateData
        //

        BioGearsStateData::
        BioGearsStateData ()
        : ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData (),
          AirwayMode_ (this),
          Intubation_ (this)
        {
        }

        BioGearsStateData::
        BioGearsStateData (const AirwayMode_type& AirwayMode,
                           const Intubation_type& Intubation)
        : ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData (),
          AirwayMode_ (AirwayMode, this),
          Intubation_ (Intubation, this)
        {
        }

        BioGearsStateData::
        BioGearsStateData (::std::unique_ptr< AirwayMode_type > AirwayMode,
                           ::std::unique_ptr< Intubation_type > Intubation)
        : ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData (),
          AirwayMode_ (std::move (AirwayMode), this),
          Intubation_ (std::move (Intubation), this)
        {
        }

        BioGearsStateData::
        BioGearsStateData (const BioGearsStateData& x,
                           ::xml_schema::flags f,
                           ::xml_schema::container* c)
        : ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData (x, f, c),
          AirwayMode_ (x.AirwayMode_, f, this),
          Intubation_ (x.Intubation_, f, this)
        {
        }

        BioGearsStateData::
        BioGearsStateData (const ::xercesc::DOMElement& e,
                           ::xml_schema::flags f,
                           ::xml_schema::container* c)
        : ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData (e, f | ::xml_schema::flags::base, c),
          AirwayMode_ (this),
          Intubation_ (this)
        {
          if ((f & ::xml_schema::flags::base) == 0)
          {
            ::xsd::cxx::xml::dom::parser< char > p (e, true, false, true);
            this->parse (p, f);
          }
        }

        void BioGearsStateData::
        parse (::xsd::cxx::xml::dom::parser< char >& p,
               ::xml_schema::flags f)
        {
          this->::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData::parse (p, f);

          for (; p.more_content (); p.next_content (false))
          {
            const ::xercesc::DOMElement& i (p.cur_element ());
            const ::xsd::cxx::xml::qualified_name< char > n (
              ::xsd::cxx::xml::dom::name< char > (i));

            // AirwayMode
            //
            {
              ::std::unique_ptr< ::xsd::cxx::tree::type > tmp (
                ::xsd::cxx::tree::type_factory_map_instance< 0, char > ().create (
                  "AirwayMode",
                  "uri:/mil/tatrc/physiology/datamodel",
                  &::xsd::cxx::tree::factory_impl< AirwayMode_type >,
                  false, true, i, n, f, this));

              if (tmp.get () != 0)
              {
                if (!AirwayMode_.present ())
                {
                  ::std::unique_ptr< AirwayMode_type > r (
                    dynamic_cast< AirwayMode_type* > (tmp.get ()));

                  if (r.get ())
                    tmp.release ();
                  else
                    throw ::xsd::cxx::tree::not_derived< char > ();

                  this->AirwayMode_.set (::std::move (r));
                  continue;
                }
              }
            }

            // Intubation
            //
            {
              ::std::unique_ptr< ::xsd::cxx::tree::type > tmp (
                ::xsd::cxx::tree::type_factory_map_instance< 0, char > ().create (
                  "Intubation",
                  "uri:/mil/tatrc/physiology/datamodel",
                  &::xsd::cxx::tree::factory_impl< Intubation_type >,
                  false, true, i, n, f, this));

              if (tmp.get () != 0)
              {
                if (!Intubation_.present ())
                {
                  ::std::unique_ptr< Intubation_type > r (
                    dynamic_cast< Intubation_type* > (tmp.get ()));

                  if (r.get ())
                    tmp.release ();
                  else
                    throw ::xsd::cxx::tree::not_derived< char > ();

                  this->Intubation_.set (::std::move (r));
                  continue;
                }
              }
            }

            break;
          }

          if (!AirwayMode_.present ())
          {
            throw ::xsd::cxx::tree::expected_element< char > (
              "AirwayMode",
              "uri:/mil/tatrc/physiology/datamodel");
          }

          if (!Intubation_.present ())
          {
            throw ::xsd::cxx::tree::expected_element< char > (
              "Intubation",
              "uri:/mil/tatrc/physiology/datamodel");
          }
        }

        BioGearsStateData* BioGearsStateData::
        _clone (::xml_schema::flags f,
                ::xml_schema::container* c) const
        {
          return new class BioGearsStateData (*this, f, c);
        }

        BioGearsStateData& BioGearsStateData::
        operator= (const BioGearsStateData& x)
        {
          if (this != &x)
          {
            static_cast< ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData& > (*this) = x;
            this->AirwayMode_ = x.AirwayMode_;
            this->Intubation_ = x.Intubation_;
          }

          return *this;
        }

        BioGearsStateData::
        ~BioGearsStateData ()
        {
        }

        static
        const ::xsd::cxx::tree::type_factory_initializer< 0, char, BioGearsStateData >
        _xsd_BioGearsStateData_type_factory_init (
          "BioGearsStateData",
          "uri:/mil/tatrc/physiology/datamodel");
      }
    }
  }
}

#include <ostream>

#include <xsd/cxx/tree/std-ostream-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::std_ostream_plate< 0, char >
  std_ostream_plate_init;
}

namespace mil
{
  namespace tatrc
  {
    namespace physiology
    {
      namespace datamodel
      {
        ::std::ostream&
        operator<< (::std::ostream& o, enumBioGearsAirwayMode::value i)
        {
          return o << enumBioGearsAirwayMode::_xsd_enumBioGearsAirwayMode_literals_[i];
        }

        ::std::ostream&
        operator<< (::std::ostream& o, const enumBioGearsAirwayMode& i)
        {
          return o << static_cast< const ::xml_schema::string& > (i);
        }

        static
        const ::xsd::cxx::tree::std_ostream_initializer< 0, char, enumBioGearsAirwayMode >
        _xsd_enumBioGearsAirwayMode_std_ostream_init;

        ::std::ostream&
        operator<< (::std::ostream& o, const BioGearsStateData& i)
        {
          o << static_cast< const ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData& > (i);

          {
            ::xsd::cxx::tree::std_ostream_map< char >& om (
              ::xsd::cxx::tree::std_ostream_map_instance< 0, char > ());

            o << ::std::endl << "AirwayMode: ";
            om.insert (o, i.AirwayMode ());
          }

          {
            ::xsd::cxx::tree::std_ostream_map< char >& om (
              ::xsd::cxx::tree::std_ostream_map_instance< 0, char > ());

            o << ::std::endl << "Intubation: ";
            om.insert (o, i.Intubation ());
          }

          return o;
        }

        static
        const ::xsd::cxx::tree::std_ostream_initializer< 0, char, BioGearsStateData >
        _xsd_BioGearsStateData_std_ostream_init;
      }
    }
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace mil
{
  namespace tatrc
  {
    namespace physiology
    {
      namespace datamodel
      {
        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (const ::std::string& u,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0,
            (f & ::xml_schema::flags::keep_dom) == 0);

          ::xsd::cxx::tree::error_handler< char > h;

          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::xsd::cxx::xml::dom::parse< char > (
              u, h, p, f));

          h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

          return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
            ::mil::tatrc::physiology::datamodel::BioGearsState (
              std::move (d), f | ::xml_schema::flags::own_dom, p));
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (const ::std::string& u,
                       ::xml_schema::error_handler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0,
            (f & ::xml_schema::flags::keep_dom) == 0);

          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::xsd::cxx::xml::dom::parse< char > (
              u, h, p, f));

          if (!d.get ())
            throw ::xsd::cxx::tree::parsing< char > ();

          return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
            ::mil::tatrc::physiology::datamodel::BioGearsState (
              std::move (d), f | ::xml_schema::flags::own_dom, p));
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (const ::std::string& u,
                       ::xercesc::DOMErrorHandler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::xsd::cxx::xml::dom::parse< char > (
              u, h, p, f));

          if (!d.get ())
            throw ::xsd::cxx::tree::parsing< char > ();

          return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
            ::mil::tatrc::physiology::datamodel::BioGearsState (
              std::move (d), f | ::xml_schema::flags::own_dom, p));
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::std::istream& is,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0,
            (f & ::xml_schema::flags::keep_dom) == 0);

          ::xsd::cxx::xml::sax::std_input_source isrc (is);
          return ::mil::tatrc::physiology::datamodel::BioGearsState (isrc, f, p);
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::std::istream& is,
                       ::xml_schema::error_handler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0,
            (f & ::xml_schema::flags::keep_dom) == 0);

          ::xsd::cxx::xml::sax::std_input_source isrc (is);
          return ::mil::tatrc::physiology::datamodel::BioGearsState (isrc, h, f, p);
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::std::istream& is,
                       ::xercesc::DOMErrorHandler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::sax::std_input_source isrc (is);
          return ::mil::tatrc::physiology::datamodel::BioGearsState (isrc, h, f, p);
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::std::istream& is,
                       const ::std::string& sid,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0,
            (f & ::xml_schema::flags::keep_dom) == 0);

          ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
          return ::mil::tatrc::physiology::datamodel::BioGearsState (isrc, f, p);
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::std::istream& is,
                       const ::std::string& sid,
                       ::xml_schema::error_handler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0,
            (f & ::xml_schema::flags::keep_dom) == 0);

          ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
          return ::mil::tatrc::physiology::datamodel::BioGearsState (isrc, h, f, p);
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::std::istream& is,
                       const ::std::string& sid,
                       ::xercesc::DOMErrorHandler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
          return ::mil::tatrc::physiology::datamodel::BioGearsState (isrc, h, f, p);
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::xercesc::InputSource& i,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xsd::cxx::tree::error_handler< char > h;

          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::xsd::cxx::xml::dom::parse< char > (
              i, h, p, f));

          h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

          return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
            ::mil::tatrc::physiology::datamodel::BioGearsState (
              std::move (d), f | ::xml_schema::flags::own_dom, p));
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::xercesc::InputSource& i,
                       ::xml_schema::error_handler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::xsd::cxx::xml::dom::parse< char > (
              i, h, p, f));

          if (!d.get ())
            throw ::xsd::cxx::tree::parsing< char > ();

          return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
            ::mil::tatrc::physiology::datamodel::BioGearsState (
              std::move (d), f | ::xml_schema::flags::own_dom, p));
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::xercesc::InputSource& i,
                       ::xercesc::DOMErrorHandler& h,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::xsd::cxx::xml::dom::parse< char > (
              i, h, p, f));

          if (!d.get ())
            throw ::xsd::cxx::tree::parsing< char > ();

          return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
            ::mil::tatrc::physiology::datamodel::BioGearsState (
              std::move (d), f | ::xml_schema::flags::own_dom, p));
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (const ::xercesc::DOMDocument& doc,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties& p)
        {
          if (f & ::xml_schema::flags::keep_dom)
          {
            ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
              static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

            return ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > (
              ::mil::tatrc::physiology::datamodel::BioGearsState (
                std::move (d), f | ::xml_schema::flags::own_dom, p));
          }

          const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
          const ::xsd::cxx::xml::qualified_name< char > n (
            ::xsd::cxx::xml::dom::name< char > (e));

          ::std::unique_ptr< ::xsd::cxx::tree::type > tmp (
            ::xsd::cxx::tree::type_factory_map_instance< 0, char > ().create (
              "BioGearsState",
              "uri:/mil/tatrc/physiology/datamodel",
              &::xsd::cxx::tree::factory_impl< ::mil::tatrc::physiology::datamodel::BioGearsStateData >,
              true, true, e, n, f, 0));

          if (tmp.get () != 0)
          {
            ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > r (
              dynamic_cast< ::mil::tatrc::physiology::datamodel::BioGearsStateData* > (tmp.get ()));

            if (r.get ())
              tmp.release ();
            else
              throw ::xsd::cxx::tree::not_derived< char > ();

            return r;
          }

          throw ::xsd::cxx::tree::unexpected_element < char > (
            n.name (),
            n.namespace_ (),
            "BioGearsState",
            "uri:/mil/tatrc/physiology/datamodel");
        }

        ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData >
        BioGearsState (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
                       ::xml_schema::flags f,
                       const ::xml_schema::properties&)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > c (
            ((f & ::xml_schema::flags::keep_dom) &&
             !(f & ::xml_schema::flags::own_dom))
            ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
            : 0);

          ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
          const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

          const ::xsd::cxx::xml::qualified_name< char > n (
            ::xsd::cxx::xml::dom::name< char > (e));

          if (f & ::xml_schema::flags::keep_dom)
            doc.setUserData (::xml_schema::dom::tree_node_key,
                             (c.get () ? &c : &d),
                             0);

          ::std::unique_ptr< ::xsd::cxx::tree::type > tmp (
            ::xsd::cxx::tree::type_factory_map_instance< 0, char > ().create (
              "BioGearsState",
              "uri:/mil/tatrc/physiology/datamodel",
              &::xsd::cxx::tree::factory_impl< ::mil::tatrc::physiology::datamodel::BioGearsStateData >,
              true, true, e, n, f, 0));

          if (tmp.get () != 0)
          {

            ::std::unique_ptr< ::mil::tatrc::physiology::datamodel::BioGearsStateData > r (
              dynamic_cast< ::mil::tatrc::physiology::datamodel::BioGearsStateData* > (tmp.get ()));

            if (r.get ())
              tmp.release ();
            else
              throw ::xsd::cxx::tree::not_derived< char > ();

            return r;
          }

          throw ::xsd::cxx::tree::unexpected_element < char > (
            n.name (),
            n.namespace_ (),
            "BioGearsState",
            "uri:/mil/tatrc/physiology/datamodel");
        }
      }
    }
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

#include <xsd/cxx/tree/type-serializer-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_serializer_plate< 0, char >
  type_serializer_plate_init;
}

namespace mil
{
  namespace tatrc
  {
    namespace physiology
    {
      namespace datamodel
      {
        void
        operator<< (::xercesc::DOMElement& e, const enumBioGearsAirwayMode& i)
        {
          e << static_cast< const ::xml_schema::string& > (i);
        }

        void
        operator<< (::xercesc::DOMAttr& a, const enumBioGearsAirwayMode& i)
        {
          a << static_cast< const ::xml_schema::string& > (i);
        }

        void
        operator<< (::xml_schema::list_stream& l,
                    const enumBioGearsAirwayMode& i)
        {
          l << static_cast< const ::xml_schema::string& > (i);
        }

        static
        const ::xsd::cxx::tree::type_serializer_initializer< 0, char, enumBioGearsAirwayMode >
        _xsd_enumBioGearsAirwayMode_type_serializer_init (
          "enumBioGearsAirwayMode",
          "uri:/mil/tatrc/physiology/datamodel");


        void
        operator<< (::xercesc::DOMElement& e, const BioGearsStateData& i)
        {
          e << static_cast< const ::mil::tatrc::physiology::datamodel::PhysiologyEngineStateData& > (i);

          // AirwayMode
          //
          {
            ::xsd::cxx::tree::type_serializer_map< char >& tsm (
              ::xsd::cxx::tree::type_serializer_map_instance< 0, char > ());

            const BioGearsStateData::AirwayMode_type& x (i.AirwayMode ());
            if (typeid (BioGearsStateData::AirwayMode_type) == typeid (x))
            {
              ::xercesc::DOMElement& s (
                ::xsd::cxx::xml::dom::create_element (
                  "AirwayMode",
                  "uri:/mil/tatrc/physiology/datamodel",
                  e));

              s << x;
            }
            else
              tsm.serialize (
                "AirwayMode",
                "uri:/mil/tatrc/physiology/datamodel",
                false, true, e, x);
          }

          // Intubation
          //
          {
            ::xsd::cxx::tree::type_serializer_map< char >& tsm (
              ::xsd::cxx::tree::type_serializer_map_instance< 0, char > ());

            const BioGearsStateData::Intubation_type& x (i.Intubation ());
            if (typeid (BioGearsStateData::Intubation_type) == typeid (x))
            {
              ::xercesc::DOMElement& s (
                ::xsd::cxx::xml::dom::create_element (
                  "Intubation",
                  "uri:/mil/tatrc/physiology/datamodel",
                  e));

              s << x;
            }
            else
              tsm.serialize (
                "Intubation",
                "uri:/mil/tatrc/physiology/datamodel",
                false, true, e, x);
          }
        }

        static
        const ::xsd::cxx::tree::type_serializer_initializer< 0, char, BioGearsStateData >
        _xsd_BioGearsStateData_type_serializer_init (
          "BioGearsStateData",
          "uri:/mil/tatrc/physiology/datamodel");


        void
        BioGearsState (::std::ostream& o,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       const ::xml_schema::namespace_infomap& m,
                       const ::std::string& e,
                       ::xml_schema::flags f)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0);

          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::mil::tatrc::physiology::datamodel::BioGearsState (s, m, f));

          ::xsd::cxx::tree::error_handler< char > h;

          ::xsd::cxx::xml::dom::ostream_format_target t (o);
          if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
          {
            h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
          }
        }

        void
        BioGearsState (::std::ostream& o,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       ::xml_schema::error_handler& h,
                       const ::xml_schema::namespace_infomap& m,
                       const ::std::string& e,
                       ::xml_schema::flags f)
        {
          ::xsd::cxx::xml::auto_initializer i (
            (f & ::xml_schema::flags::dont_initialize) == 0);

          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::mil::tatrc::physiology::datamodel::BioGearsState (s, m, f));
          ::xsd::cxx::xml::dom::ostream_format_target t (o);
          if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
          {
            throw ::xsd::cxx::tree::serialization< char > ();
          }
        }

        void
        BioGearsState (::std::ostream& o,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       ::xercesc::DOMErrorHandler& h,
                       const ::xml_schema::namespace_infomap& m,
                       const ::std::string& e,
                       ::xml_schema::flags f)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::mil::tatrc::physiology::datamodel::BioGearsState (s, m, f));
          ::xsd::cxx::xml::dom::ostream_format_target t (o);
          if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
          {
            throw ::xsd::cxx::tree::serialization< char > ();
          }
        }

        void
        BioGearsState (::xercesc::XMLFormatTarget& t,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       const ::xml_schema::namespace_infomap& m,
                       const ::std::string& e,
                       ::xml_schema::flags f)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::mil::tatrc::physiology::datamodel::BioGearsState (s, m, f));

          ::xsd::cxx::tree::error_handler< char > h;

          if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
          {
            h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
          }
        }

        void
        BioGearsState (::xercesc::XMLFormatTarget& t,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       ::xml_schema::error_handler& h,
                       const ::xml_schema::namespace_infomap& m,
                       const ::std::string& e,
                       ::xml_schema::flags f)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::mil::tatrc::physiology::datamodel::BioGearsState (s, m, f));
          if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
          {
            throw ::xsd::cxx::tree::serialization< char > ();
          }
        }

        void
        BioGearsState (::xercesc::XMLFormatTarget& t,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       ::xercesc::DOMErrorHandler& h,
                       const ::xml_schema::namespace_infomap& m,
                       const ::std::string& e,
                       ::xml_schema::flags f)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
            ::mil::tatrc::physiology::datamodel::BioGearsState (s, m, f));
          if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
          {
            throw ::xsd::cxx::tree::serialization< char > ();
          }
        }

        void
        BioGearsState (::xercesc::DOMDocument& d,
                       const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       ::xml_schema::flags)
        {
          ::xercesc::DOMElement& e (*d.getDocumentElement ());
          const ::xsd::cxx::xml::qualified_name< char > n (
            ::xsd::cxx::xml::dom::name< char > (e));

          if (typeid (::mil::tatrc::physiology::datamodel::BioGearsStateData) == typeid (s))
          {
            if (n.name () == "BioGearsState" &&
                n.namespace_ () == "uri:/mil/tatrc/physiology/datamodel")
            {
              e << s;
            }
            else
            {
              throw ::xsd::cxx::tree::unexpected_element < char > (
                n.name (),
                n.namespace_ (),
                "BioGearsState",
                "uri:/mil/tatrc/physiology/datamodel");
            }
          }
          else
          {
            ::xsd::cxx::tree::type_serializer_map_instance< 0, char > ().serialize (
              "BioGearsState",
              "uri:/mil/tatrc/physiology/datamodel",
              e, n, s);
          }
        }

        ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument >
        BioGearsState (const ::mil::tatrc::physiology::datamodel::BioGearsStateData& s,
                       const ::xml_schema::namespace_infomap& m,
                       ::xml_schema::flags f)
        {
          ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d;

          if (typeid (::mil::tatrc::physiology::datamodel::BioGearsStateData) == typeid (s))
          {
            d = ::xsd::cxx::xml::dom::serialize< char > (
              "BioGearsState",
              "uri:/mil/tatrc/physiology/datamodel",
              m, f);
          }
          else
          {
            d = ::xsd::cxx::tree::type_serializer_map_instance< 0, char > ().serialize (
              "BioGearsState",
              "uri:/mil/tatrc/physiology/datamodel",
              m, s, f);
          }

          ::mil::tatrc::physiology::datamodel::BioGearsState (*d, s, f);
          return d;
        }
      }
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

