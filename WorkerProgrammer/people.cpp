#include "people.h"

#include <stdexcept>

using namespace std;

Person::Person(const string& name, int age, Gender gender) : name_(name), age_(age), gender_(gender) {
}

const string& Person::GetName() const {
    return name_;
}

int Person::GetAge() const {
    return age_;
}

Gender Person::GetGender() const {
    return gender_;
}

void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {
    programming_languages_.insert(language);
}

bool Programmer::CanProgram(ProgrammingLanguage language) const {
    return programming_languages_.count(language) > 0 ? true : false;
}

void Worker::AddSpeciality(WorkerSpeciality speciality) {
    worker_specialities_.insert(speciality);
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {
    return worker_specialities_.count(speciality) > 0 ? true : false;
}

