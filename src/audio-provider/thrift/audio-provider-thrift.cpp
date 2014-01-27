/* audio-provider-thrift.cpp
 *
 * Copyright 2014 Yegor Mazur <yegor.mazur@gmail.com>
 *
 * This file is part of Melange.
 *
 * Melange is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Melange is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Melange. If not, see <http://www.gnu.org/licenses/>.
 */

#include "audio-provider.h"
#include <iostream>

AudioAdaptor::AudioAdaptor()
{
	if (m_VmcTransport.get())
	{
		m_VmcTransport->close();
	}
	m_VmcSocket.reset(new TSocket("localhost", 9090));
	m_VmcTransport.reset(new TBufferedTransport(m_VmcSocket));
	m_VmcProtocol.reset(new TBinaryProtocol(m_VmcTransport));
	m_VmcAudioClient.reset(new AudioAdaptorClient(m_VmcProtocol));
	m_VmcTransport->open();
}

void AudioAdaptor::GetPlayBackDevices(std::vector<std::string> &dev)
{
	int number = m_VmcAudioClient->GetPlayoutDeviceNumber();
	
	for (int i = 0; i < number; i++)
	{
		std::string strNameUTF8;
		
		m_VmcAudioClient->GetPlayoutDeviceName(strNameUTF8, i);
		dev.push_back(strNameUTF8);
	}
}

void AudioAdaptor::GetRecordingDevices(std::vector<std::string> &dev)
{
	int number = m_VmcAudioClient->GetRecordingDeviceNumber();
	
	for (int i = 0; i < number; i++)
	{
		std::string strNameUTF8;
		
		m_VmcAudioClient->GetRecordingDeviceName(strNameUTF8, i);
		dev.push_back(strNameUTF8);
	}
}

void AudioAdaptor::SetPlayoutDevice(const std::string &dev)
{
	m_VmcAudioClient->SetPlayoutDevice(dev);
}

void AudioAdaptor::SetRecordingDevice(const std::string &dev)
{
	m_VmcAudioClient->SetRecordingDevice(dev);
}

unsigned int AudioAdaptor::GetMicrophoneLevel()
{
	return m_VmcAudioClient->GetSpeechInputLevel();
}

void AudioAdaptor::PlayTone()
{
	m_VmcAudioClient->PlayTone();
}

void AudioAdaptor::StartMicTest()
{
	m_VmcAudioClient->StartMicTest();
}

void AudioAdaptor::StopMicTest()
{
	m_VmcAudioClient->StopMicTest();
}

void AudioAdaptor::MakeCall(std::string &addr)
{
	m_VmcAudioClient->MakeCall(addr);
}

void AudioAdaptor::EndCall()
{
	m_VmcAudioClient->EndCall();
}

AudioAdaptor::~AudioAdaptor()
{

}