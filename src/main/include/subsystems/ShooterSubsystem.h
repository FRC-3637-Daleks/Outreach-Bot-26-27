#pragma once

#include <rev/SparkMax.h>
#include <rev/SparkFlex.h>
#include "Constants.h"

class ShooterSubsystem {
    public:
        void Init();
        void SetPosition(double targetRotations);
        void ZeroEncoder();
        void Stop();
        double GetPosition();
        void SetSpeed(double speed);

    private:
        rev::spark::SparkMax m_shooterArmMotor{
            ShooterConstants::kShooterArmMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkFlex m_shooterMotor{
            ShooterConstants::kShooterWheelMotorID,
            rev::spark::SparkFlex::MotorType::kBrushless};
        
};