#include "subsystems/ShooterSubsystem.h"
#include <algorithm>

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
    rev::PersistMode::kPersistParameters
  );

  rev::spark::SparkBaseConfig config1{};
  config1.Inverted(true);
  config1.SmartCurrentLimit(ShooterConstants::kShooterCurrentLimit);
  
  m_ShooterMotor.Configure(
    config1,
    rev::ResetMode::kResetSafeParameters,
    rev::PersistMode::kPersistParameters
  );
  
  m_shooterArmMotor.GetEncoder().SetPosition(0.0);
  ReturnToShooterAngle();
}

void ShooterSubsystem::CommandArmAngle(double angleDegrees) {
  if (m_isHoming) {
    return;
  }

  double clampedAngle = std::clamp(
    angleDegrees,
    ShooterConstants::kStowAngleDeg,
    ShooterConstants::kIntakeAngleDeg
  );

  double targetRotations = clampedAngle * (ShooterConstants::kGearRatio / 360.0);

  m_shooterArmMotor.GetClosedLoopController().SetSetpoint(
    targetRotations,
    rev::spark::SparkLowLevel::ControlType::kPosition
  );
}

void ShooterSubsystem::StartHoming() {
  m_isHoming = true;
  m_isFiring = false;
  m_currentSpikeCount = 0;
  m_ShooterMotor.StopMotor();
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
      ReturnToShooterAngle();
    }
  } else {
    m_currentSpikeCount = 0;
  }
}

bool ShooterSubsystem::IsHoming() const {
  return m_isHoming;
}

void ShooterSubsystem::SetAngleDegrees(double targetDegrees) {
  CommandArmAngle(targetDegrees);
}

void ShooterSubsystem::SetShooterAngle(double angleDegrees) {
  m_rememberedShooterAngle = std::clamp(
    angleDegrees,
    ShooterConstants::kStowAngleDeg,
    ShooterConstants::kIntakeAngleDeg
  );

  if (!m_isIntaking && !m_isCatching && !m_isHoming) {
    CommandArmAngle(m_rememberedShooterAngle);
  }
}

void ShooterSubsystem::ReturnToShooterAngle() {
  m_isIntaking = false;
  m_isCatching = false;
  m_isFiring = false;
  m_ShooterMotor.StopMotor();
  CommandArmAngle(m_rememberedShooterAngle);
}

double ShooterSubsystem::GetAngleDegrees() {
  double rotations = m_shooterArmMotor.GetEncoder().GetPosition();
  return rotations * (360.0 / ShooterConstants::kGearRatio);
}

double ShooterSubsystem::GetRememberedShooterAngle() const {
  return m_rememberedShooterAngle;
}

void ShooterSubsystem::SetGroundIntake(bool intaking) {
  m_isHoming = false;
  m_isFiring = false;
  m_isIntaking = true;
  m_isCatching = false;

  CommandArmAngle(ShooterConstants::kActivePosition);
  m_ShooterMotor.Set(ShooterConstants::kIntakeSpeed);
}

void ShooterSubsystem::SetCatch() {
  m_isHoming = false;
  m_isFiring = false;
  m_isIntaking = false;
  m_isCatching = true;

  CommandArmAngle(ShooterConstants::kCatchingPosition);
  m_ShooterMotor.Set(ShooterConstants::kIntakeSpeed);
}

void ShooterSubsystem::SetIntaking(bool intaking) {
  m_isIntaking = intaking;
  if (m_isIntaking) {
    m_isCatching = false;
    m_isFiring = false;
    CommandArmAngle(ShooterConstants::kActivePosition);
    m_ShooterMotor.Set(ShooterConstants::kIntakeSpeed);
  } else if (!m_isCatching && m_isFiring) {
    m_ShooterMotor.StopMotor();
  }
}

void ShooterSubsystem::SetCatching(bool catching) {
  m_isCatching = catching;
  if (m_isCatching) {
    m_isIntaking = false;
    m_isFiring = false;
    CommandArmAngle(ShooterConstants::kCatchingPosition);
    m_ShooterMotor.Set(ShooterConstants::kIntakeSpeed);
  } else if (!m_isIntaking && !m_isFiring) {
    m_ShooterMotor.StopMotor();
  }
}

void ShooterSubsystem::UpdateIntakeOrCatch(double distanceInches) {
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

void ShooterSubsystem::Stop() {
  m_isHoming = false;
  m_isIntaking = false;
  m_isCatching = false;
  m_isFiring = false;
  m_currentSpikeCount = 0;
  m_shooterArmMotor.StopMotor();
  m_ShooterMotor.StopMotor();
}

void ShooterSubsystem::StopRoller() {
  m_isIntaking = false;
  m_isCatching = false;
  m_isFiring = false;
  m_ShooterMotor.StopMotor();
}