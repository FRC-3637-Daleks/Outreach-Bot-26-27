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
        rev::PersistMode::kPersistParameters
    );

    rev::spark::SparkBaseConfig config1{};
    config.Inverted(false);
    config.OpenLoopRampRate(ShooterConstants::kRampRateSeconds);

    m_shooterMotor.Configure(
        config1,
        rev::ResetMode::kResetSafeParameters,
        rev::PersistMode::kPersistParameters);
}

void ShooterSubsystem::SetPosition(double targetRotations) {
    m_shooterArmMotor.GetClosedLoopController().SetSetpoint(
        targetRotations,
        rev::spark::SparkLowLevel::ControlType::kPosition);
}

void ShooterSubsystem::ZeroEncoder() {
    m_shooterArmMotor.GetEncoder().SetPosition(0.0);
}

void ShooterSubsystem::Stop() {
    m_shooterArmMotor.StopMotor();
    m_shooterMotor.StopMotor();
}

double ShooterSubsystem::GetPosition() {
    return m_shooterArmMotor.GetEncoder().GetPosition();
}

void ShooterSubsystem::SetSpeed(double speed) {
    double clamped = std::clamp(speed, -ShooterConstants::kMaxSpeed, ShooterConstants::kMaxSpeed);
    m_shooterMotor.Set(clamped);
}