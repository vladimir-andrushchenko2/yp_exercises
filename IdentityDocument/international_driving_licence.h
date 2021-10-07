#pragma once

#include "driving_licence.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class InternationalDrivingLicence {
public:
    InternationalDrivingLicence() {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "InternationalDrivingLicence::Ctor()"sv << std::endl;
    }

    InternationalDrivingLicence(const InternationalDrivingLicence& other)
        : parent_(other.parent_)
    {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "InternationalDrivingLicence::CCtor()"sv << std::endl;
    }

    ~InternationalDrivingLicence() {
        parent_.ResetVTablePtr();
        std::cout << "InternationalDrivingLicence::Dtor()"sv << std::endl;
    }

    operator const DrivingLicence* () const {
        return &parent_;
    }

    operator DrivingLicence() {
        return {parent_};
    }

    void PrintID() const {
        std::cout << "InternationalDrivingLicence::PrintID() : "sv << parent_.GetID() << std::endl;
    }

    void Delete() {
        this->~InternationalDrivingLicence();
    }

private:
    struct VTable {
        using T = void (InternationalDrivingLicence::*)() const;
        using U = void (InternationalDrivingLicence::*)();

        T print_id = {&InternationalDrivingLicence::PrintID };
        U delete_impl = {&InternationalDrivingLicence::Delete };
    };

private:
    DrivingLicence parent_;
    static VTable vtable_;
};

InternationalDrivingLicence::VTable InternationalDrivingLicence::vtable_ = {InternationalDrivingLicence::PrintID, InternationalDrivingLicence::Delete };
