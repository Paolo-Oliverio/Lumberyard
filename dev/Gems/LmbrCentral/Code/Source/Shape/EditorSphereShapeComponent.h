/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once
#include "SphereShapeComponent.h"
#include "EditorBaseShapeComponent.h"
#include <AzCore/std/containers/array.h>
#include <LmbrCentral/Shape/SphereShapeComponentBus.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <AzToolsFramework/API/ToolsApplicationAPI.h>
#include <AzToolsFramework/Manipulators/LinearManipulator.h>

namespace LmbrCentral
{   
    class EditorSphereShapeComponent
        : public EditorBaseShapeComponent
        , public SphereShape
		, private AzToolsFramework::EntitySelectionEvents::Bus::Handler
    {
    public:

        AZ_EDITOR_COMPONENT(EditorSphereShapeComponent, EditorSphereShapeComponentTypeId, EditorBaseShapeComponent);
        static void Reflect(AZ::ReflectContext* context);

        ~EditorSphereShapeComponent() override = default;
        
        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;        
        
        // EditorComponentBase implementation
        void BuildGameEntity(AZ::Entity* gameEntity) override;                
        void DrawShape(AzFramework::EntityDebugDisplayRequests* displayContext) const override;        

        SphereShapeConfig& GetConfiguration() override
        {
            return m_configuration;
        }
    protected:

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            EditorBaseShapeComponent::GetProvidedServices(provided);
            provided.push_back(AZ_CRC("SphereShapeService", 0x90c8dc80));
        }

    private:

        void ConfigurationChanged();

		/// AzToolsFramework::EntitySelectionEvents::Bus::Handler
		void OnSelected() override;
		void OnDeselected() override;

        SphereShapeConfig m_configuration;

		// Linear Manipulators
		void RegisterManipulators();
		void UnregisterManipulators();
		void UpdateManipulators();

		void OnMouseMoveManipulator(
			const AzToolsFramework::LinearManipulator::Action& action, const AZ::Vector3& axis);

		AZStd::unique_ptr<AzToolsFramework::LinearManipulator> m_linearManipulator;
    };
} // namespace LmbrCentral
