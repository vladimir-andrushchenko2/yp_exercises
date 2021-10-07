#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class TravelPack {
public:
    TravelPack()
        : identity_doc1_((IdentityDocument*) new Passport())
        , identity_doc2_((IdentityDocument*) new DrivingLicence())
    {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "TravelPack::Ctor()"sv << std::endl;
    }

    TravelPack(const TravelPack& other)
        : identity_doc1_((IdentityDocument*) new Passport(*reinterpret_cast<Passport*>(other.identity_doc1_)))
        , identity_doc2_((IdentityDocument*) new Passport(*reinterpret_cast<Passport*>(other.identity_doc2_)))
        , additional_pass_(other.additional_pass_)
        , additional_dr_licence_(other.additional_dr_licence_) 
    {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "TravelPack::CCtor()"sv << std::endl;
    }

    ~TravelPack() {
        identity_doc1_->Delete();
        identity_doc2_->Delete();
        parent_.ResetVTablePtr();
        std::cout << "TravelPack::Dtor()"sv << std::endl;
    }

    void PrintID() const{
        identity_doc1_->PrintID();
        identity_doc2_->PrintID();
        additional_pass_.PrintID();
        additional_dr_licence_.PrintID();
    }

    operator IdentityDocument() { return {parent_}; }

    void Delete() {
        this->~TravelPack();
    }

private:
    struct VTable {
        using PrintIDType = void (TravelPack::*) () const;
        using DeleteType = void (TravelPack::*) () ;

        PrintIDType print_id = { &TravelPack::PrintID };
        DeleteType delete_impl = { &TravelPack::Delete };
    };

private:
    static VTable vtable_;

    IdentityDocument parent_;

    IdentityDocument* identity_doc1_;
    IdentityDocument* identity_doc2_;
    Passport additional_pass_;
    DrivingLicence additional_dr_licence_;
};

TravelPack::VTable TravelPack::vtable_ = { TravelPack::PrintID, TravelPack::Delete };
