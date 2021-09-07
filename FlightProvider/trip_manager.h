#pragma once
#include <string>
#include <vector>

#include "flight_provider.h"
#include "hotel_provider.h"

class Trip {
   public:
    Trip(HotelProvider& hp, FlightProvider& fp) : hp_(hp), fp_(fp) {}
    Trip(const Trip&) = delete;
    Trip(Trip&& other) = default;
    Trip& operator=(const Trip&) = delete;
    Trip& operator=(Trip&&) = delete;
    void Cancel() {
        for (const FlightProvider::BookingId flight_id : flights) {
            fp_.Cancel(flight_id);
        }
        
        for (const HotelProvider::BookingId hotel_id : hotels) {
            hp_.Cancel(hotel_id);
        }
    }
    ~Trip() {
        Cancel();
    }

   public:
    std::vector<FlightProvider::BookingId> flights;
    std::vector<HotelProvider::BookingId> hotels;

   private:
    HotelProvider& hp_;
    FlightProvider& fp_;
};

class TripManager {
   public:
    using BookingId = std::string;
    struct BookingData {
        std::string city_from;
        std::string city_to;
        std::string date_from;
        std::string date_to;
    };

    Trip Book(const BookingData&) {
        Trip trip(hotel_provider_, flight_provider_);
        {
            FlightProvider::BookingData flight_booking_data;
            trip.flights.push_back(flight_provider_.Book(flight_booking_data));
        }
        {
            HotelProvider::BookingData hotel_booking_data;
            trip.hotels.push_back(hotel_provider_.Book(hotel_booking_data));
        }
        {
            FlightProvider::BookingData flight_booking_data;
            trip.flights.push_back(flight_provider_.Book(flight_booking_data));
        }
        return trip;
    }

    void Cancel(Trip& trip) { trip.Cancel(); }

   private:
    HotelProvider hotel_provider_;
    FlightProvider flight_provider_;
};
