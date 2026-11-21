#pragma once

#include <rev/SparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include "Constants.h"

class DriveSubsystem {
    public:
        void Init();
        void ArcadeDrive(double forward, double turn);
        void Stop();

    private:
        rev::spark::SparkMax m_LFDrive{
            DriveConstants::kLeftFrontMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_LBDrive{
            DriveConstants::kLeftBackMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_RFDrive{
            DriveConstants::kRightFrontMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};
        rev::spark::SparkMax m_RBDrive{
            DriveConstants::kRightBackMotorID,
            rev::spark::SparkMax::MotorType::kBrushless};

        frc::DifferentialDrive m_drive{m_LFDrive, m_RFDrive};
};