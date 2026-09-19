/*
 * Problem Statement:
 * Design an Object-Oriented Parking Lot System:
 * - Vehicle types: Motorcycle, Car, Bus.
 * - Spot types: Small (Motorcycle only), Medium (Car or Motorcycle), Large (Bus, Car, Motorcycle).
 * - Multi-level parking lot with ability to park vehicle, unpark vehicle, and display free spots.
 * 
 * Asked in: Amazon, Google, Microsoft, Uber, Atlassian
 */

import java.util.ArrayList;
import java.util.List;

class ParkingLotSystemDesign {

    enum VehicleType { MOTORCYCLE, CAR, BUS }
    enum SpotSize { SMALL, MEDIUM, LARGE }

    abstract static class Vehicle {
        private final String licensePlate;
        private final VehicleType type;

        public Vehicle(String licensePlate, VehicleType type) {
            this.licensePlate = licensePlate;
            this.type = type;
        }

        public String getLicensePlate() { return licensePlate; }
        public VehicleType getType() { return type; }
        public abstract boolean canFitInSpot(ParkingSpot spot);
    }

    static class Motorcycle extends Vehicle {
        public Motorcycle(String licensePlate) { super(licensePlate, VehicleType.MOTORCYCLE); }
        @Override
        public boolean canFitInSpot(ParkingSpot spot) { return true; } // Fits in any spot
    }

    static class Car extends Vehicle {
        public Car(String licensePlate) { super(licensePlate, VehicleType.CAR); }
        @Override
        public boolean canFitInSpot(ParkingSpot spot) {
            return spot.getSize() == SpotSize.MEDIUM || spot.getSize() == SpotSize.LARGE;
        }
    }

    static class Bus extends Vehicle {
        public Bus(String licensePlate) { super(licensePlate, VehicleType.BUS); }
        @Override
        public boolean canFitInSpot(ParkingSpot spot) {
            return spot.getSize() == SpotSize.LARGE;
        }
    }

    static class ParkingSpot {
        private final int spotNumber;
        private final SpotSize size;
        private Vehicle currentVehicle;

        public ParkingSpot(int spotNumber, SpotSize size) {
            this.spotNumber = spotNumber;
            this.size = size;
        }

        public boolean isAvailable() { return currentVehicle == null; }
        public SpotSize getSize() { return size; }
        public int getSpotNumber() { return spotNumber; }
        public Vehicle getCurrentVehicle() { return currentVehicle; }

        public boolean park(Vehicle v) {
            if (isAvailable() && v.canFitInSpot(this)) {
                this.currentVehicle = v;
                return true;
            }
            return false;
        }

        public void unpark() { this.currentVehicle = null; }
    }

    static class ParkingLot {
        private final List<ParkingSpot> spots = new ArrayList<>();

        public void addSpot(ParkingSpot spot) {
            spots.add(spot);
        }

        public boolean parkVehicle(Vehicle v) {
            for (ParkingSpot spot : spots) {
                if (spot.isAvailable() && spot.park(v)) {
                    System.out.printf("Parked %s [%s] in spot #%d (%s)%n",
                            v.getType(), v.getLicensePlate(), spot.getSpotNumber(), spot.getSize());
                    return true;
                }
            }
            System.out.printf("Failed to park %s [%s]: No suitable spot available.%n",
                    v.getType(), v.getLicensePlate());
            return false;
        }

        public boolean unparkVehicle(String licensePlate) {
            for (ParkingSpot spot : spots) {
                if (!spot.isAvailable() && spot.getCurrentVehicle().getLicensePlate().equals(licensePlate)) {
                    System.out.printf("Vehicle [%s] vacated spot #%d%n", licensePlate, spot.getSpotNumber());
                    spot.unpark();
                    return true;
                }
            }
            System.out.println("Vehicle [" + licensePlate + "] not found in parking lot.");
            return false;
        }
    }

    public static void main(String[] args) {
        ParkingLot lot = new ParkingLot();
        lot.addSpot(new ParkingSpot(101, SpotSize.SMALL));
        lot.addSpot(new ParkingSpot(102, SpotSize.MEDIUM));
        lot.addSpot(new ParkingSpot(103, SpotSize.LARGE));

        Vehicle moto = new Motorcycle("MOTO-100");
        Vehicle sedan = new Car("CAR-200");
        Vehicle bus = new Bus("BUS-300");
        Vehicle suv = new Car("SUV-400");

        System.out.println("--- Testing Parking Lot Operations ---");
        lot.parkVehicle(moto);   // Spot 101 (Small)
        lot.parkVehicle(sedan);  // Spot 102 (Medium)
        lot.parkVehicle(bus);    // Spot 103 (Large)
        lot.parkVehicle(suv);    // No spots available!

        lot.unparkVehicle("CAR-200"); // Free spot 102
        lot.parkVehicle(suv);         // Spot 102 (Medium) now fits suv!
    }
}

/*
 * Time Complexity: O(S) per park/unpark where S is total number of spots.
 * Space Complexity: O(S) memory to store parking spots and vehicle references.
 */
