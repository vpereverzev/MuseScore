/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "fluidsynth.h"

#include <thread>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <fluidsynth.h>
//#include "fluid_synth.h"

#include "log.h"
#include "audioerrors.h"
#include "audiotypes.h"

using namespace mu;
using namespace mu::midi;
using namespace mu::audio;
using namespace mu::audio::synth;

static const double FLUID_GLOBAL_VOLUME_GAIN{ 1.8 };

/// @note
///  Fluid does not support MONO, so they start counting audio channels from 1, which means "1 pair of audio channels"
/// @see https://www.fluidsynth.org/api/settings_synth.html
static const audioch_t FLUID_AUDIO_CHANNELS_PAIR = 1;

static std::map<std::string, fluid_sfont_t*> s_soundFontCache;

static void* findCachedSoundFont(const char* fileName)
{
    std::string str(fileName);

    auto search = s_soundFontCache.find(str);

    if (search != s_soundFontCache.end()) {
        return search->second;
    }

    return nullptr;
}

int default_fclose(void* handle)
{
    return std::fclose(static_cast<FILE*>(handle)) == 0 ? FLUID_OK : FLUID_FAILED;
}

long default_ftell(void* handle)
{
    return std::ftell(static_cast<FILE*>(handle));
}

int safe_fread(void* buf, int count, void* fd)
{
    if (std::fread(buf, count, 1, static_cast<FILE*>(fd)) != 1) {
        if (std::feof(static_cast<FILE*>(fd))) {
            return FLUID_FAILED;
        }
    }

    return FLUID_OK;
}

int safe_fseek(void* fd, long ofs, int whence)
{
    if (std::fseek(static_cast<FILE*>(fd), ofs, whence) != 0) {
        return FLUID_FAILED;
    }

    return FLUID_OK;
}

struct mu::audio::synth::Fluid {
    fluid_settings_t* settings = nullptr;
    fluid_synth_t* synth = nullptr;

    ~Fluid()
    {
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
    }
};

FluidSynth::FluidSynth()
{
    m_fluid = std::make_shared<Fluid>();
}

bool FluidSynth::isValid() const
{
    return hasLoadedSoundFonts();
}

std::string FluidSynth::name() const
{
    return "Fluid";
}

SoundFontFormats FluidSynth::soundFontFormats() const
{
    return { SoundFontFormat::SF2, SoundFontFormat::SF3 };
}

Ret FluidSynth::init()
{
    auto fluid_log_out = [](int level, const char* message, void*) {
        switch (level) {
        case FLUID_PANIC:
        case FLUID_ERR:  {
            LOGE() << message;
        } break;
        case FLUID_WARN: {
            LOGW() << message;
        } break;
        case FLUID_INFO: {
            LOGI() << message;
        } break;
        case FLUID_DBG:  {
            LOGD() << message;
        } break;
        }

        if (level < FLUID_DBG) {
            bool debugme = true;
            (void)debugme;
        }
    };

    fluid_set_log_function(FLUID_PANIC, fluid_log_out, nullptr);
    fluid_set_log_function(FLUID_ERR, fluid_log_out, nullptr);
    fluid_set_log_function(FLUID_WARN, fluid_log_out, nullptr);
    fluid_set_log_function(FLUID_INFO, fluid_log_out, nullptr);
    fluid_set_log_function(FLUID_DBG, fluid_log_out, nullptr);

    m_fluid->settings = new_fluid_settings();
    fluid_settings_setnum(m_fluid->settings, "synth.gain", FLUID_GLOBAL_VOLUME_GAIN);
    fluid_settings_setint(m_fluid->settings, "synth.audio-channels", FLUID_AUDIO_CHANNELS_PAIR); // 1 pair of audio channels
    fluid_settings_setint(m_fluid->settings, "synth.lock-memory", 0);
    fluid_settings_setint(m_fluid->settings, "synth.threadsafe-api", 0);
    fluid_settings_setint(m_fluid->settings, "synth.midi-channels", 80);

    if (m_sampleRate > 0) {
        fluid_settings_setnum(m_fluid->settings, "synth.sample-rate", static_cast<double>(m_sampleRate));
    }

    //fluid_settings_setint(_fluid->settings, "synth.min-note-length", 50);
    //fluid_settings_setint(_fluid->settings, "synth.polyphony", conf.polyphony);

    fluid_settings_setstr(m_fluid->settings, "synth.chorus.active", 0);
//    fluid_settings_setnum(m_fluid->settings, "synth.chorus.depth", 8);
//    fluid_settings_setnum(m_fluid->settings, "synth.chorus.level", 10);
//    fluid_settings_setint(m_fluid->settings, "synth.chorus.nr", 4);
//    fluid_settings_setnum(m_fluid->settings, "synth.chorus.speed", 1);

    /*
 https://github.com/FluidSynth/fluidsynth/wiki/UserManual
 rev_preset
        num:0 roomsize:0.2 damp:0.0 width:0.5 level:0.9
        num:1 roomsize:0.4 damp:0.2 width:0.5 level:0.8
        num:2 roomsize:0.6 damp:0.4 width:0.5 level:0.7
        num:3 roomsize:0.8 damp:0.7 width:0.5 level:0.6
        num:4 roomsize:0.8 damp:1.0 width:0.5 level:0.5
*/

//    fluid_settings_setstr(m_fluid->settings, "synth.reverb.active", 0);
//    fluid_settings_setnum(m_fluid->settings, "synth.reverb.room-size", 0.8);
//    fluid_settings_setnum(m_fluid->settings, "synth.reverb.damp", 1.0);
//    fluid_settings_setnum(m_fluid->settings, "synth.reverb.width", 0.5);
//    fluid_settings_setnum(m_fluid->settings, "synth.reverb.level", 0.5);

    fluid_settings_setstr(m_fluid->settings, "audio.sample-format", "float");

    m_fluid->synth = new_fluid_synth(m_fluid->settings);

    LOGD() << "synth inited\n";
    return true;
}

void FluidSynth::setSampleRate(unsigned int sampleRate)
{
    m_sampleRate = sampleRate;
    if (m_fluid->settings) {
        fluid_settings_setnum(m_fluid->settings, "synth.sample-rate", static_cast<double>(m_sampleRate));
        m_preallocated.resize(int(m_sampleRate) * 2);
    }
}

Ret FluidSynth::addSoundFonts(const std::vector<io::path>& sfonts)
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return make_ret(Err::SynthNotInited);
    }

    bool ok = true;
    for (const io::path& path : sfonts) {

        auto search = s_soundFontCache.find(path.toStdString());

        if (search == s_soundFontCache.end() || !search->second) {
            int ret = fluid_synth_sfload(m_fluid->synth, path.c_str(), 0);

            if (ret == FLUID_FAILED) {
                continue;
            }

            fluid_sfont_t* sfont = fluid_synth_get_sfont_by_id(m_fluid->synth, ret);
            s_soundFontCache.emplace(path.toStdString(), sfont);

            LOGI() << "successfully loaded soundfont: " << path;
        } else {

            fluid_sfloader_t* loader = new_fluid_defsfloader(m_fluid->settings);
            fluid_sfloader_set_callbacks(loader,
                                         findCachedSoundFont,
                                         safe_fread,
                                         safe_fseek,
                                         default_ftell,
                                         default_fclose);

            fluid_synth_add_sfloader(m_fluid->synth, loader);

            LOGI() << "using cached soundfont: " << path;
        }
    }

    return ok ? make_ret(Err::NoError) : make_ret(Err::SoundFontFailedLoad);
}

Ret FluidSynth::removeSoundFonts()
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return make_ret(Err::SynthNotInited);
    }

    if (!hasLoadedSoundFonts()) {
        return make_ret(Err::NoError);
    }

    bool ok = true;

    int count = fluid_synth_sfcount(m_fluid->synth);

    for (int i = 0; i < count; ++i) {
        fluid_sfont_t* sfont = fluid_synth_get_sfont(m_fluid->synth, i);

        fluid_synth_sfunload(m_fluid->synth, fluid_sfont_get_id(sfont), 0);
    }

    return ok ? make_ret(Err::NoError) : make_ret(Err::SoundFontFailedUnload);
}

Ret FluidSynth::setupMidiChannels(const std::vector<Event>& events)
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return make_ret(Err::SynthNotInited);
    }

    if (!hasLoadedSoundFonts()) {
        LOGE() << "sound fonts not loaded";
        return make_ret(Err::SoundFontNotLoaded);
    }

    fluid_synth_program_reset(m_fluid->synth);
    fluid_synth_system_reset(m_fluid->synth);

    std::set<channel_t> channels;
    for (const Event& e: events) {
        channels.insert(e.channel());
    }

    for (channel_t ch : channels) {
        fluid_synth_set_interp_method(m_fluid->synth, ch, FLUID_INTERP_DEFAULT);
        fluid_synth_pitch_wheel_sens(m_fluid->synth, ch, 12);
    }

    for (const Event& e: events) {
        handleEvent(e);
    }

    return make_ret(Err::NoError);
}

bool FluidSynth::handleEvent(const Event& e)
{
    if (e.isChannelVoice20()) {
        auto events = e.toMIDI10();
        bool ret = true;
        for (auto& event : events) {
            ret &= handleEvent(event);
        }
        return ret;
    }

    if (m_isLoggingSynthEvents) {
        LOGD() << e.to_string();
    }

    int ret = FLUID_OK;
    switch (e.opcode()) {
    case Event::Opcode::NoteOn: {
        ret = fluid_synth_noteon(m_fluid->synth, e.channel(), e.note(), e.velocity());
    } break;
    case Event::Opcode::NoteOff: {
        ret = fluid_synth_noteoff(m_fluid->synth, e.channel(), e.note());
    } break;
    case Event::Opcode::ControlChange: {
        if (e.index() == CntrType::CTRL_PROGRAM) {
            ret = fluid_synth_program_change(m_fluid->synth, e.channel(), e.program());
        } else {
            ret = fluid_synth_cc(m_fluid->synth, e.channel(), e.index(), e.data());
        }
    } break;
    case Event::Opcode::ProgramChange: {
        fluid_synth_program_change(m_fluid->synth, e.channel(), e.program());
    } break;
    case Event::Opcode::PitchBend: {
        ret = fluid_synth_pitch_bend(m_fluid->synth, e.channel(), e.data());
    } break;
    default: {
        LOGW() << "not supported event type: " << e.opcodeString();
        ret = FLUID_FAILED;
    }
    }

    return ret == FLUID_OK;
}

void FluidSynth::allSoundsOff()
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return;
    }

    fluid_synth_all_notes_off(m_fluid->synth, -1);
    fluid_synth_all_sounds_off(m_fluid->synth, -1);
}

void FluidSynth::flushSound()
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return;
    }

    fluid_synth_all_notes_off(m_fluid->synth, -1);
    fluid_synth_all_sounds_off(m_fluid->synth, -1);

    int size = int(m_sampleRate);

    fluid_synth_write_float(m_fluid->synth, size, &m_preallocated[0], 0, 1, &m_preallocated[0], size, 1);
}

void FluidSynth::midiChannelSoundsOff(channel_t chan)
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return;
    }

    fluid_synth_all_sounds_off(m_fluid->synth, chan);
}

bool FluidSynth::midiChannelVolume(channel_t chan, float volume)
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return false;
    }

    int val = static_cast<int>(volume * 100.f);
    val = std::clamp(val, 0, 127);

    int ret = fluid_synth_cc(m_fluid->synth, chan, VOLUME_MSB, val);
    return ret == FLUID_OK;
}

bool FluidSynth::midiChannelBalance(channel_t chan, float balance)
{
    IF_ASSERT_FAILED(m_fluid->synth) {
        return false;
    }

    balance = std::clamp(balance, -1.f, 1.f);
    float normalized = (balance < 0 ? 63 : 64) + 63 * balance;
    int val = static_cast<int>(std::lround(normalized));
    val = std::clamp(val, 0, 127);

    int ret = fluid_synth_cc(m_fluid->synth, chan, PAN_MSB, val);
    return ret == FLUID_OK;
}

bool FluidSynth::midiChannelPitch(channel_t chan, int16_t pitch)
{
    // 0-16383 with 8192 being center

    IF_ASSERT_FAILED(m_fluid->synth) {
        return false;
    }

    pitch = std::clamp(pitch, static_cast<int16_t>(-12), static_cast<int16_t>(12));

    int32_t val = (8192 * pitch) / 12;
    val = 8192 + val;
    val = std::clamp(val, 0, 16383);

    int ret = fluid_synth_pitch_bend(m_fluid->synth, chan, val);
    return ret == FLUID_OK;
}

bool FluidSynth::isActive() const
{
    return m_isActive;
}

void FluidSynth::setIsActive(bool arg)
{
    m_isActive = arg;
}

void FluidSynth::writeBuf(float* stream, unsigned int samples)
{
    IF_ASSERT_FAILED(samples > 0) {
        return;
    }

    fluid_synth_write_float(m_fluid->synth, static_cast<int>(samples),
                            stream, 0, audioChannelsCount(),
                            stream, 1, audioChannelsCount());
}

unsigned int FluidSynth::audioChannelsCount() const
{
    return FLUID_AUDIO_CHANNELS_PAIR * 2;
}

void FluidSynth::process(float* buffer, unsigned int sampleCount)
{
    writeBuf(buffer, sampleCount);
}

async::Channel<unsigned int> FluidSynth::audioChannelsCountChanged() const
{
    return m_streamsCountChanged;
}

bool FluidSynth::hasLoadedSoundFonts() const
{
    return fluid_synth_sfcount(m_fluid->synth) == 0;
}
