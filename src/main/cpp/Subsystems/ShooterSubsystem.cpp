#include "subsystems/ShooterSubsystem.h"

void ShooterSubsystem::Init() {
  rev::spark::SparkBaseConfig config{};
  config.Inverted(false);
  config.SmartCurrentLimit(ShooterConstants::kShooterCurrentLimit);

  config.closedLoop
      .P(ShooterConstants::kP)
      .I(ShooterConstants::kI)
      .D(ShooterConstants::kD)
      .OutputRange(ShooterConstants::kMinOutput, ShooterConstants::kMaxOutput);

  m_shooterArmMotor.Configure(
      config,
      rev::ResetMode::kResetSafeParameters,
      rev::PersistMode::kPersistParameters);

  rev::spark::SparkBaseConfig config1{};
  config.Inverted(true);
  
  m_ShooterMotor.Configure(
    config1,
    rev::ResetMode::kResetSafeParameters,
    rev::PersistMode::kPersistParameters
  );

}

void ShooterSubsystem::StartHoming() {
  m_isHoming = true;
  m_currentSpikeCount = 0;
  m_shooterArmMotor.Set(ShooterConstants::kHomingSpeed);
}

void ShooterSubsystem::UpdateHoming() {
  if (!m_isHoming) {
    return;
  }

  m_shooterArmMotor.Set(ShooterConstants::kHomingSpeed);

  if (m_shooterArmMotor.GetOutputCurrent() >= ShooterConstants::kHomingCurrentAmps) {
    m_currentSpikeCount++;
    if (m_currentSpikeCount >= ShooterConstants::kHomingDebounceCycles) {
      m_shooterArmMotor.StopMotor();
      m_shooterArmMotor.GetEncoder().SetPosition(0.0);
      m_isHoming = false;
      m_currentSpikeCount = 0;
    }
  } else {
    m_currentSpikeCount = 0;
  }
}

bool ShooterSubsystem::IsHoming() const {
  return m_isHoming;
}

void ShooterSubsystem::SetAngleDegrees(double targetDegrees) {
  if (m_isHoming) {
    return;
  }

  double targetRotations = targetDegrees * (ShooterConstants::kGearRatio / 360.0);
  m_shooterArmMotor.GetClosedLoopController().SetSetpoint(
      targetRotations,
      rev::spark::SparkLowLevel::ControlType::kPosition);
}

double ShooterSubsystem::GetAngleDegrees() {
  double rotations = m_shooterArmMotor.GetEncoder().GetPosition();
  return rotations * (360.0 / ShooterConstants::kGearRatio);
}

void ShooterSubsystem::Stop() {
  m_isHoming = false;
  m_currentSpikeCount = 0;
  m_shooterArmMotor.StopMotor();
  m_ShooterMotor.StopMotor();
}

void ShooterSubsystem::SetIntaking(bool intaking) {
  m_isIntaking = intaking;
}

void ShooterSubsystem::SetCatching(bool catching) {
  m_isCatching = catching;
}

void ShooterSubsystem::UpdateIntakeOrCatch(bool distanceInches) {
  if ((!m_isIntaking && !m_isCatching) || m_isHoming) {
    return;
  }

  m_ShooterMotor.Set(ShooterConstants::kIntakeSpeed);

  if (distanceInches > 0.0 && distanceInches <= ShooterConstants::kUSStopDistance) {
    m_ShooterMotor.StopMotor();
    m_isIntaking = false;
    m_isCatching = false;
    StartHoming();
  }
}

void ShooterSubsystem::StopRoller() {
  m_ShooterMotor.StopMotor();
}