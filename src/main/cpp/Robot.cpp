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
<<<<<<< HEAD
        m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kActivePosition);
    } else if (m_driverController.GetBButtonPressed()) {
        m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kRestPostition);
=======
        m_shooterSubsystem.SetPosition(ShooterConstants::kActivePosition);
    } else if (m_driverController.GetBButtonPressed()) {
        m_shooterSubsystem.SetPosition(ShooterConstants::kRestPostition);
>>>>>>> 726937232b4cc79982008f681f2aafb4dd4ef934
    }
}

void Robot::DisabledInit() {
    m_driveSubsystem.Stop();
}

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<Robot>();
}
<<<<<<< HEAD
#endif
//
=======
#endif
>>>>>>> 726937232b4cc79982008f681f2aafb4dd4ef934
