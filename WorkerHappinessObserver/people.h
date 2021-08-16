#pragma once

#include <string>
#include <iostream>

using namespace std;

class Person;

// Наблюдатель за состоянием человека.
class PersonObserver {
   public:
    // Этот метод вызывается, когда меняется состояние удовлетворённости человека
    virtual void OnSatisfactionChanged(Person& /*person*/, int /*old_value*/, int /*new_value*/) {
        // Реализация метода базового класса ничего не делает
    }

   protected:
    // Класс PersonObserver не предназначен для удаления напрямую
    ~PersonObserver() = default;
};

/*
    Человек.
    При изменении уровня удовлетворённости уведомляет
    связанного с ним наблюдателя
*/
class Person {
   public:
    Person(const std::string& name, int age) : name_(name), age_(age) {}

    const std::string& GetName() const { return name_; }

    int GetSatisfaction() const { return satisfaction_; }

    // «Привязывает» наблюдателя к человеку. Привязанный наблюдатель
    // уведомляется об изменении уровня удовлетворённости человека
    // Новый наблюдатель заменяет собой ранее привязанного
    // Если передать nullptr в качестве наблюдателя, это эквивалентно отсутствию наблюдателя
    void SetObserver(PersonObserver* observer) { observer_ = observer; }

    int GetAge() const { return age_; }

    // Увеличивает на 1 количество походов на танцы
    // Увеличивает удовлетворённость на 1
    virtual void Dance() {
        ++dance_count_;
        SetSatisfaction(GetSatisfaction() + 1);
    }

    int GetDanceCount() const { return dance_count_; }

    // Прожить день. Реализация в базовом классе ничего не делает
    virtual void LiveADay() {
        // Подклассы могут переопределить этот метод
    }

    virtual ~Person() = default;

   protected:
    void SetSatisfaction(int value) {
        if (satisfaction_ != value) {
            int old_satisfaction = satisfaction_;
            satisfaction_ = value;
            // Если у человека есть наблюдатель, сообщаем ему об изменении удовлетворённости
            if (observer_) {
                observer_->OnSatisfactionChanged(*this, old_satisfaction, satisfaction_);
            }
        }
    }

   private:
    std::string name_;
    PersonObserver* observer_ = nullptr;
    int satisfaction_ = 100;
    int age_{};

    int dance_count_{};
};

// Рабочий.
// День рабочего проходит за работой
class Worker : public Person {
   public:
    Worker(const std::string& name, int age) : Person(name, age) {}

    // Рабочий старше 30 лет и младше 40 за танец получает 2 единицы удовлетворённости вместо 1
    void Dance() override {
        // Рабочий сперва просто танцует, как обычный человек
        Person::Dance();

        // Рабочий в возрасте от 30 до 40 во время танца получает
        // дополнительную порцию удовлетворения
        if (const int age = GetAge(); age > 30 && age < 40) {
            SetSatisfaction(GetSatisfaction() + 1);
        }
    }

    // День рабочего проходит за работой
    void LiveADay() override {
        Work();
    }

    // Увеличивает счётчик сделанной работы на 1, уменьшает удовлетворённость на 5
    void Work() {
        SetSatisfaction(GetSatisfaction() - 5);
        ++work_counter_;
    }

    // Возвращает значение счётчика сделанной работы
    int GetWorkDone() const {
        return work_counter_;
    }

   private:
    int work_counter_{};
};

// Студент.
// День студента проходит за учёбой
class Student : public Person {
   public:
    Student(const std::string& name, int age) : Person(name, age) {}

    // День студента проходит за учёбой
    void LiveADay() override {
        Study();
    }

    // Учёба увеличивает уровень знаний на 1, уменьшает уровень удовлетворённости на 3
    void Study() {
        SetSatisfaction(GetSatisfaction() - 3);
        ++knowledge_counter_;
    }

    // Возвращает уровень знаний
    int GetKnowledgeLevel() const {
        return knowledge_counter_;
    }

    private:
    int knowledge_counter_{};
};
