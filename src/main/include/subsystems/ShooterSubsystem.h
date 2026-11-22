#pragma once

#include <rev/SparkMax.h>
#include <rev/SparkFlex.h>
#include "Constants.h"

class ShooterSubsystem {
    public:
        void Init();
        void StartHoming();
        void UpdateHoming();
        bool IsHoming() const;
        void Stop();
        void SetSpeed(double speed);
        void SetAngleDegrees(double targetDegrees);
        double GetAngleDegrees();

    private:
        rev::spark::SparkMax m_shooterArmMotor{
            ShooterConstants::kShooterArmMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkFlex m_shooterMotor{
            ShooterConstants::kShooterWheelMotorID,
            rev::spark::SparkFlex::MotorType::kBrushless};

        bool m_isHoming{false};
        int m_currentSpikeCount{0};
        
};
//
