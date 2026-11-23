#include <units/length.h>
#include "Robot.h"
#include "Constants.h"

void Robot::RobotInit() {
    m_driveSubsystem.Init();
    m_shooterSubsystem.Init();

    frc::Ultrasonic::SetAutomaticMode(true);
}

void Robot::TeleopPeriodic() {
    m_driveSubsystem.ArcadeDrive(
        m_driverController.GetLeftY(),
        m_driverController.GetRightX()
    );

    if (m_driverController.GetAButtonPressed()) {
    m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kActivePosition);
    m_shooterSubsystem.SetIntaking(true);
    m_shooterSubsystem.SetCatching(false);
  } else if (m_driverController.GetYButtonPressed()) {
    m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kCatchingPosition);
    m_shooterSubsystem.SetIntaking(false);
    m_shooterSubsystem.SetCatching(true);
  } else if (m_driverController.GetBButtonPressed()) {
    m_shooterSubsystem.SetIntaking(false);
    m_shooterSubsystem.SetCatching(false);
    m_shooterSubsystem.StopRoller();
    m_shooterSubsystem.SetAngleDegrees(ShooterConstants::kRestPosition);
  }

    units::meter_t distance = m_rangeFinder.GetRange();
    units::inch_t distanceInches = distance;
    m_shooterSubsystem.UpdateIntakeOrCatch(distanceInches.value());

    if (m_shooterSubsystem.IsHoming()) {
        m_shooterSubsystem.UpdateHoming();
    }
}

void Robot::DisabledInit() {
    m_driveSubsystem.Stop();
    m_shooterSubsystem.Stop();
}

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<Robot>();
}
#endif