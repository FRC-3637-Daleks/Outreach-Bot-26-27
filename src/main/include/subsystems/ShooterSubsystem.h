#pragma once

#include <rev/SparkMax.h>
#include <rev/SparkFlex.h>
#include "Constants.h"

class ShooterSubsystem {
    public:
        void Init();
<<<<<<< HEAD
        void StartHoming();
        void UpdateHoming();
        bool IsHoming() const;
        void Stop();
        void SetSpeed(double speed);
        void SetAngleDegrees(double targetDegrees);
        double GetAngleDegrees();
=======
        void SetPosition(double targetRotations);
        void ZeroEncoder();
        void Stop();
        double GetPosition();
        void SetSpeed(double speed);
>>>>>>> 726937232b4cc79982008f681f2aafb4dd4ef934

    private:
        rev::spark::SparkMax m_shooterArmMotor{
            ShooterConstants::kShooterArmMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkFlex m_shooterMotor{
            ShooterConstants::kShooterWheelMotorID,
            rev::spark::SparkFlex::MotorType::kBrushless};
<<<<<<< HEAD

        bool m_isHoming{false};
        int m_currentSpikeCount{0};
        
};
//
=======
        
};
>>>>>>> 726937232b4cc79982008f681f2aafb4dd4ef934
