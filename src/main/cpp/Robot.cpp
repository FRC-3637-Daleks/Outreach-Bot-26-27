#include "Robot.h"

void Robot::RobotInit() {
    m_driveSubsystem.Init();
}

void Robot::TeleopPeriodic() {
    m_driveSubsystem.ArcadeDrive(
        m_driverController.GetLeftY(),
        m_driverController.GetRightX()
    );

    if (m_driverController.GetAButtonPressed()) {
        m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kActivePosition);
    } else if (m_driverController.GetBButtonPressed()) {
        m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kRestPostition);
    }
}

void Robot::DisabledInit() {
    m_driveSubsystem.Stop();
}

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<Robot>();
}
#endif