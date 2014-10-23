#include "../../../../Include/Trambo/Inputs/joystickAxisAsButton.h"
#include "../../../../Include/Trambo/Events/event.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>

#include <cassert>


namespace trmb
{

JoystickAxisAsButton::JoystickAxisAsButton(sf::Joystick::Axis axis, ButtonType buttonType, unsigned int joystickId, float onState, float offState)
: mInput(axis)
, mButtonType(buttonType)
, mJoystickId(joystickId)
, mOnState(onState)
, mOffState(offState)
, mPreviousState(State::Off)
, mCurrentState(State::Off)
{
	assert(sf::Joystick::AxisCount > axis);
}

sf::Joystick::Axis JoystickAxisAsButton::getInput() const
{
	return mInput;
}

JoystickAxisAsButton::ButtonType JoystickAxisAsButton::getButtonType() const
{
	return mButtonType;
}

float JoystickAxisAsButton::getOnState() const
{
	return mOnState;
}

float JoystickAxisAsButton::getOffState() const
{
	return mOffState;
}

void JoystickAxisAsButton::update(ActionWeakPtr actionWeakPtr)
{
	realTime(actionWeakPtr);
}

void JoystickAxisAsButton::handleEvent(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	onPress(inputEvent, actionWeakPtr);
	onRelease(inputEvent, actionWeakPtr);
}

void JoystickAxisAsButton::realTime(ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::RealTime == mButtonType)
	{
		const float position = sf::Joystick::getAxisPosition(mJoystickId, mInput);
		if (mOnState == position)
		{
			ActionSharedPtr actionSharedPtr = actionWeakPtr.lock(); // ALW - get shared_ptr from weak_ptr
			if (!actionSharedPtr)
			{
				assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
			}

			actionSharedPtr->sendEvent();
		}
	}
}

void JoystickAxisAsButton::onPress(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnPress == mButtonType && mJoystickId == inputEvent.joystickButton.joystickId)
	{
		if (mInput == inputEvent.joystickMove.axis)
		{
			mPreviousState = mCurrentState;
			if (mOnState == inputEvent.joystickMove.position)
			{
				mCurrentState = State::On;
			}
			else
			{
				mCurrentState = State::Off;
			}

			if (mCurrentState == State::On && mPreviousState == State::Off)
			{
				ActionSharedPtr actionSharedPtr = actionWeakPtr.lock(); // ALW - get shared_ptr from weak_ptr
				if (!actionSharedPtr)
				{
					assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
				}

				actionSharedPtr->sendEvent();
			}
		}
	}
}

void JoystickAxisAsButton::onRelease(const sf::Event& inputEvent, ActionWeakPtr actionWeakPtr)
{
	if (ButtonType::OnRelease == mButtonType && mJoystickId == inputEvent.joystickButton.joystickId)
	{
		if (mInput == inputEvent.joystickMove.axis)
		{
			mPreviousState = mCurrentState;
			if (mOnState == inputEvent.joystickMove.position)
			{
				mCurrentState = State::On;
			}
			else
			{
				mCurrentState = State::Off;
			}

			if (mCurrentState == State::Off && mPreviousState == State::On)
			{
				ActionSharedPtr actionSharedPtr = actionWeakPtr.lock(); // ALW - get shared_ptr from weak_ptr
				if (!actionSharedPtr)
				{
					assert(("ALW - Logic Error: The managed object in mActions has been deleted!", false));
				}

				actionSharedPtr->sendEvent();
			}
		}
	}
}

} // namespace trmb
