/*
 * Problem Statement:
 * Design an Object-Oriented Parking Lot System:
 * - Vehicle types: Motorcycle, Car, Bus.
 * - Spot types: Small (Motorcycle only), Medium (Car or Motorcycle), Large (Bus, Car, Motorcycle).
 * - Multi-level parking lot with ability to park vehicle, unpark vehicle, and display free spots.
 * 
 * Asked in: Amazon, Google, Microsoft, Uber, Atlassian
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

enum VehicleType { MOTORCYCLE, CAR, BUS }
    enum SpotSize { SMALL, MEDIUM, LARGE }

    abstract static class Vehicle {
        static const const char* licensePlate;
        static const VehicleType type;

        Vehicle(const char* licensePlate, VehicleType type) {
            this.licensePlate = licensePlate;
            this.type = type;
        }

        const char* getLicensePlate() { return licensePlate; }
        VehicleType getType() { return type; }
        abstract bool canFitInSpot(ParkingSpot spot);
    }

    static class Motorcycle extends Vehicle {
        Motorcycle(const char* licensePlate) { super(licensePlate, VehicleType.MOTORCYCLE); }
        bool canFitInSpot(ParkingSpot spot) { return true; } // Fits in any spot
    }

    static class Car extends Vehicle {
        Car(const char* licensePlate) { super(licensePlate, VehicleType.CAR); }
        bool canFitInSpot(ParkingSpot spot) {
            return spot.getSize() == SpotSize.MEDIUM || spot.getSize() == SpotSize.LARGE;
        }
    }

    static class Bus extends Vehicle {
        Bus(const char* licensePlate) { super(licensePlate, VehicleType.BUS); }
        bool canFitInSpot(ParkingSpot spot) {
            return spot.getSize() == SpotSize.LARGE;
        }
    }

    static class ParkingSpot {
        static const int spotNumber;
        static const SpotSize size;
        static Vehicle currentVehicle;

        ParkingSpot(int spotNumber, SpotSize size) {
            this.spotNumber = spotNumber;
            this.size = size;
        }

        bool isAvailable() { return currentVehicle == NULL; }
        SpotSize getSize() { return size; }
        int getSpotNumber() { return spotNumber; }
        Vehicle getCurrentVehicle() { return currentVehicle; }

        bool park(Vehicle v) {
            if (isAvailable() && v.canFitInSpot(this)) {
                this.currentVehicle = v;
                return true;
            }
            return false;
        }

        void unpark() { this.currentVehicle = NULL; }
    }

    static class ParkingLot {
        static const int* spots = new ArrayList<>();

        void addSpot(ParkingSpot spot) {
            spots.add(spot);
        }

        bool parkVehicle(Vehicle v) {
            for (ParkingSpot spot : spots) {
                if (spot.isAvailable() && spot.park(v)) {
                    printf("Parked %s [%s] in spot #%d (%s)\n",
                            v.getType(), v.getLicensePlate(), spot.getSpotNumber(), spot.getSize());
                    return true;
                }
            }
            printf("Failed to park %s [%s]: No suitable spot available.\n",
                    v.getType(), v.getLicensePlate());
            return false;
        }

        bool unparkVehicle(const char* licensePlate) {
            for (ParkingSpot spot : spots) {
                if (!spot.isAvailable() && spot.getCurrentVehicle().getLicensePlate().equals(licensePlate)) {
                    printf("Vehicle [%s] vacated spot #%d\n", licensePlate, spot.getSpotNumber());
                    spot.unpark();
                    return true;
                }
            }
            printf("Vehicle [" + licensePlate + "] not found in parking lot.\n");
            return false;
        }
    }

    int main(void) {
        ParkingLot lot = new ParkingLot();
        lot.addSpot(new ParkingSpot(101, SpotSize.SMALL));
        lot.addSpot(new ParkingSpot(102, SpotSize.MEDIUM));
        lot.addSpot(new ParkingSpot(103, SpotSize.LARGE));

        Vehicle moto = new Motorcycle("MOTO-100");
        Vehicle sedan = new Car("CAR-200");
        Vehicle bus = new Bus("BUS-300");
        Vehicle suv = new Car("SUV-400");

        printf("--- Testing Parking Lot Operations ---\n");
        lot.parkVehicle(moto);   // Spot 101 (Small)
        lot.parkVehicle(sedan);  // Spot 102 (Medium)
        lot.parkVehicle(bus);    // Spot 103 (Large)
        lot.parkVehicle(suv);    // No spots available!

        lot.unparkVehicle("CAR-200"); // Free spot 102
        lot.parkVehicle(suv);         // Spot 102 (Medium) now fits suv!
        return 0;
}

/*
 * Time Complexity: O(S) per park/unpark where S is total number of spots.
 * Space Complexity: O(S) memory to store parking spots and vehicle references.
 */
