#include "subsystems/DriveSubsystem.h"
#include <algorithm>
#include <cmath>

void DriveSubsystem::Init() {
 rev::spark::SparkBaseConfig LFDriveConfig{};
 rev::spark::SparkBaseConfig LBDriveConfig{};
 rev::spark::SparkBaseConfig RFDriveConfig{};
 rev::spark::SparkBaseConfig RBDriveConfig{};

 LBDriveConfig.Follow(m_LFDrive);
 RBDriveConfig.Follow(m_RFDrive);

 RFDriveConfig.Inverted(true);

 m_LFDrive.Configure(
      LFDriveConfig,
      rev::ResetMode::kResetSafeParameters,
      rev::PersistMode::kPersistParameters);

  m_LBDrive.Configure(
      LBDriveConfig,
      rev::ResetMode::kResetSafeParameters,
      rev::PersistMode::kPersistParameters);

  m_RFDrive.Configure(
      RFDriveConfig,
      rev::ResetMode::kResetSafeParameters,
      rev::PersistMode::kPersistParameters);

  m_RBDrive.Configure(
      RBDriveConfig,
      rev::ResetMode::kResetSafeParameters,
      rev::PersistMode::kPersistParameters);
}

void DriveSubsystem::ArcadeDrive(double forward, double turn) {
  double left_wheel_speed = forward + turn;
  double right_wheel_speed = forward - turn;

  double highest_speed = std::max(std::abs(left_wheel_speed), std::abs(right_wheel_speed));
  if (highest_speed > 1) {
    left_wheel_speed /= highest_speed;
    right_wheel_speed /= highest_speed;
  }

  m_drive.TankDrive(DriveConstants::kMaxDriveSpeed * left_wheel_speed, DriveConstants::kMaxDriveSpeed * right_wheel_speed);
}

void DriveSubsystem::Stop() {
  m_drive.TankDrive(0, 0);
}