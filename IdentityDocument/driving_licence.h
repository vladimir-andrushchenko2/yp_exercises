#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class DrivingLicence {
public:
    DrivingLicence() {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "DrivingLicence::Ctor()"sv << std::endl;
    }

    DrivingLicence(const DrivingLicence& other)
        : parent_(other.parent_)
    {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "DrivingLicence::CCtor()"sv << std::endl;
    }

    ~DrivingLicence() {
        parent_.ResetVTablePtr();
        std::cout << "DrivingLicence::Dtor()"sv << std::endl;
    }

    operator const IdentityDocument* () const {
        return &parent_;
    }

    operator IdentityDocument() { return {parent_}; }

    void PrintID() const{
        std::cout << "DrivingLicence::PrintID() : "sv << parent_.GetID() << std::endl;
    }

    void Delete() {
        this->~DrivingLicence();
    }

    int GetID() const {
        return parent_.GetID();
    }

    void SetVTablePtr(void* new_ptr) {
        vtable_ptr_ = new_ptr;
    }

    void ResetVTablePtr() {
        vtable_ptr_ = &vtable_;
    }


private:
    struct VTable {
        using PrintIDType = void (DrivingLicence::*) () const;
        using DeleteType = void (DrivingLicence::*) () ;

        PrintIDType print_id = { &DrivingLicence::PrintID };
        DeleteType delete_impl = { &DrivingLicence::Delete };
    };

private:
    IdentityDocument parent_;

    static DrivingLicence::VTable vtable_;
    void* vtable_ptr_ = { &vtable_ };
};

DrivingLicence::VTable DrivingLicence::vtable_ = { DrivingLicence::PrintID, DrivingLicence::PrintID };
