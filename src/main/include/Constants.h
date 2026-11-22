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
    //shooter wheels
    constexpr int kShooterWheelMotorID = 7;
    constexpr double kMaxSpeed = 0.85; // %
    constexpr double kRampRateSeconds = 0.25;

    //shooter arm
    constexpr int kShooterArmMotorID = 6;
    constexpr int kShooterCurrentLimit = 40;
    constexpr double kP = 0.05;
    constexpr double kI = 0.0;
    constexpr double kD = 0.0;

    constexpr double kMinOutput = -0.4;
    constexpr double kMaxOutput = 0.4;

    constexpr double kRestPostition = 0.0;
    constexpr double kActivePosition = 10.0;

    constexpr double kGearRatio = 4.0;

    constexpr double kStowAngleDeg = 0.0;
    constexpr double kIntakeAngleDeg = 180.0;
    constexpr double kCatchAngleDeg = 60;

    constexpr double kHomingSpeed = -0.15;
    constexpr double kHomingCurrentAmps = 12.0;
    constexpr int kHomingDebounceCycles = 5;
    //
}