#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std::string_view_literals;

class Passport {
public:
    Passport()
        : expiration_date_(GetExpirationDate()) 
    {
        parent_.SetVTablePtr(&vtable_);
        std::cout << "Passport::Ctor()"sv << std::endl;
    }

    ~Passport() {
        parent_.ResetVTablePtr();
        std::cout << "Passport::Dtor()"sv << std::endl;
    }

    Passport(const Passport& other)
        : parent_(other.parent_)
        , expiration_date_(other.expiration_date_) 
    {
        std::cout << "Passport::CCtor()"sv << std::endl;
    }

    operator const IdentityDocument* () const {
        return &parent_;
    }

    operator IdentityDocument() {
        IdentityDocument identity_document;
        identity_document.ResetVTablePtr();
        return identity_document;
    }

    void PrintID()const {
        std::cout << "Passport::PrintID() : "sv << parent_.GetID();
        std::cout << " expiration date : "sv << expiration_date_.tm_mday << "/"sv << expiration_date_.tm_mon << "/"sv
                  << expiration_date_.tm_year + 1900 << std::endl;
    }

    void SetVTablePtr(void* new_ptr) {
        vtable_ptr_ = new_ptr;
    }

    void ResetVTablePtr() {
        vtable_ptr_ = &vtable_;
    }

    void PrintVisa(const std::string& country) const {
        auto print_visa_ptr = static_cast<VTable*>(&vtable_)->print_visa;
        (this->*print_visa_ptr)(country);
    }

    void Delete() {
        this->~Passport();
    }

    static void PrintUniqueIDCount() {
        IdentityDocument::PrintUniqueIDCount();
    }

private:
    void PrintVisaImpl(const std::string& country) const {
        std::cout << "Passport::PrintVisa("sv << country << ") : "sv << parent_.GetID() << std::endl;
    }

private:
    struct VTable {
        using DeleteType = void (Passport::*)();
        using PrintIDType = void (Passport::*)() const;
        using PrintVisaType = void (Passport::*)(const std::string&) const;

        PrintIDType print_id = { &Passport::PrintID };
        DeleteType delete_impl = {&Passport::Delete };
        PrintVisaType print_visa = {&Passport::PrintVisaImpl };
    };

private:
    static VTable vtable_;
    void* vtable_ptr_ = { &vtable_ };

    IdentityDocument parent_;

    const struct tm expiration_date_;

    tm GetExpirationDate() {
	    time_t t = time(nullptr);
	    tm exp_date = *localtime(&t);
	    exp_date.tm_year += 10;
	    mktime(&exp_date);
	    return exp_date;
	}
};

Passport::VTable Passport::vtable_ = {};
