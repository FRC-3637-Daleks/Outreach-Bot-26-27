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
        void SetAngleDegrees(double targetDegrees);
        double GetAngleDegrees();

        void SetIntaking(bool intaking);
        void SetCatching(bool catching);
        void UpdateIntakeOrCatch(bool distanceInches);

        void Stop();
        void StopRoller();

    private:
        rev::spark::SparkMax m_shooterArmMotor{
            ShooterConstants::kShooterArmMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkFlex m_ShooterMotor{
            ShooterConstants::kShooterWheelMotorID,
            rev::spark::SparkFlex::MotorType::kBrushless};

        bool m_isHoming{false};
        int m_currentSpikeCount{0};

        bool m_isIntaking{false};
        bool m_isCatching{false};
};