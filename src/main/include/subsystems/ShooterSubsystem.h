#pragma once

#include <rev/SparkFlex.h>
#include <rev/SparkMax.h>
#include "Constants.h"

class ShooterSubsystem {
    public:
        void Init();

        void StartHoming();
        void UpdateHoming();
        bool IsHoming() const;

        void SetAngleDegrees(double targetDegrees);
        void SetShooterAngle(double angleDegrees);
        void AdjustShooterAngle(double deltaDegrees);
        void ReturnToShooterAngle();
        double GetAngleDegrees();
        double GetRememberedShooterAngle() const;

        void SetGroundIntake(bool intaking);
        void SetCatch();
        void SetIntaking(bool intaking);
        void SetCatching(bool catching);
        void UpdateIntakeOrCatch(double distanceInches);
        void SetFiring(bool firing);

        void Stop();
        void StopRoller();

    private:
        void CommandArmAngle(double angleDegrees);

        rev::spark::SparkMax m_shooterArmMotor{
            ShooterConstants::kShooterArmMotorID,
            rev::spark::SparkMax::MotorType::kBrushless
        };
        rev::spark::SparkFlex m_ShooterMotor{
            ShooterConstants::kShooterWheelMotorID,
            rev::spark::SparkFlex::MotorType::kBrushless
        };

    bool m_isHoming{false};
    int m_currentSpikeCount{0};

    bool m_isIntaking{false};
    bool m_isCatching{false};
    bool m_isFiring{false};

    double m_rememberedShooterAngle{ShooterConstants::kDefaultShooterAngle};
};