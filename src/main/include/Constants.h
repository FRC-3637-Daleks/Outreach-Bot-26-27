#pragma once

namespace OperatorConstants {
    constexpr int kDriverControllerPort = 0;
    constexpr int kOperatorControllerPort = 1;    
}

namespace DriveConstants {
    constexpr int kLeftFrontMotorID = 2;
    constexpr int kLeftBackMotorID = 3;
    constexpr int kRightFrontMotorID = 4;
    constexpr int kRightBackMotorID = 5;

    constexpr double kMaxDriveSpeed = 0.5; // %
    constexpr int kDriveCurrentLimit = 40;
}

namespace ShooterConstants {
    // Shooter Arm
    constexpr int kShooterArmMotorID = 6;
    constexpr int kShooterCurrentLimit = 40;
    constexpr double kP = 0.05;
    constexpr double kI = 0.0;
    constexpr double kD = 0.0;

    constexpr double kMinOutput = -0.4;
    constexpr double kMaxOutput = 0.4;

    constexpr double kRestPostition = 0.0;
    constexpr double kActivePosition = 10.0;

    // Shooter Wheels
    constexpr int kShooterWheelMotorID = 7;
    constexpr double kMaxSpeed = 0.85; // %
    constexpr double kRampRateSeconds = 0.25;
}