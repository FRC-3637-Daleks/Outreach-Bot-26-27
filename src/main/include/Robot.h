#pragma once

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/Ultrasonic.h>
#include "Constants.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/ShooterSubsystem.h"

class Robot : public frc::TimedRobot {
    public:
        void RobotInit() override;
        void TeleopPeriodic() override;
        void DisabledInit() override;

        bool kIsIntaking = false;
        bool kIsCatching = false;
        double kUSDistance = 0;

    private:
        DriveSubsystem m_driveSubsystem;
        ShooterSubsystem m_shooterSubsystem;

        frc::XboxController m_driverController{OperatorConstants::kDriverControllerPort};

        frc::Ultrasonic m_rangeFinder{0, 1};
};