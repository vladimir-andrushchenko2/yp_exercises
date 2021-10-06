#pragma once

#include <iostream>
#include <string>

using namespace std::string_view_literals;

class IdentityDocument {
public:
    IdentityDocument()
        : unique_id_(++unique_id_count_) 
    {
        std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
    }

    ~IdentityDocument() {
        --unique_id_count_;
        std::cout << "IdentityDocument::Dtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument(const IdentityDocument& other)
        : unique_id_(++unique_id_count_) 
    {
        std::cout << "IdentityDocument::CCtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument& operator=(const IdentityDocument&) = delete;

    void SetVTablePtr(void* new_ptr) {
        vtable_ptr_ = new_ptr;
    }

    void ResetVTablePtr() {
        vtable_ptr_ = &vtable_;
    }

    void PrintID() const {
        auto print_id_ptr = static_cast<VTable*>(vtable_ptr_)->print_id;
        (this->*print_id_ptr)();
    }

    void Delete() {
        auto delete_ptr = static_cast<VTable*>(vtable_ptr_)->delete_impl;
        (this->*delete_ptr)();
    }

    static void PrintUniqueIDCount() {
        std::cout << "unique_id_count_ : "sv << unique_id_count_ << std::endl;
    }

    int GetID() const {
        return unique_id_;
    }

private:
    void PrintIDImpl() const {
        std::cout << "IdentityDocument::PrintID() : "sv << unique_id_ << std::endl;
    }

    void DeleteImpl() {
        this->~IdentityDocument();
    }

private:
    struct VTable {
        using PrintIDType = void (IdentityDocument::*)() const;
        using DeleteType = void (IdentityDocument::*)() ;

        PrintIDType print_id = { &IdentityDocument::PrintIDImpl };
        DeleteType delete_impl = { &IdentityDocument::DeleteImpl };
    };

private:
    static VTable vtable_;
    void* vtable_ptr_ = { &vtable_ };

    static int unique_id_count_;
    int unique_id_;
};

IdentityDocument::VTable IdentityDocument::vtable_ = {};

int IdentityDocument::unique_id_count_ = 0;
