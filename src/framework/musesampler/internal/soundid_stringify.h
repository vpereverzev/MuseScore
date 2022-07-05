/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2022 MuseScore BVBA and others
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

#ifndef MU_SOUNDID_STRINGIFY_H
#define MU_SOUNDID_STRINGIFY_H

#include <map>
#include <string>

#include "mpe/soundid.h"

namespace mu::mpe {

static const std::map<SoundId, std::string> SoundIdToString
{
    {SoundId::Undefined, "Undefined"},

    {SoundId::Accordion, "Accordion"},
    {SoundId::Bandoneon, "Bandoneon"},
    {SoundId::Concertina, "Concertina"},
    {SoundId::Harmonica, "Harmonica"},
    {SoundId::Melodica, "Melodica"},
    {SoundId::Sheng, "Sheng"},
    {SoundId::Celesta, "Celesta"},
    {SoundId::Clavichord, "Clavichord"},
    {SoundId::Harpsichord, "Harpsichord"},
    {SoundId::Virginal, "Virginal"},
    {SoundId::Piano, "Piano"},
    {SoundId::Organ, "Organ"},
    {SoundId::Harmonium, "Harmonium"},
    {SoundId::Synthesizer, "Synthesizer"},
    {SoundId::Theremin, "Theremin"},
    {SoundId::OndesMartenot, "OndesMartenot"},

    {SoundId::Harp, "Harp"},
    {SoundId::Cavaquinho, "Cavaquinho"},
    {SoundId::Guitar, "Guitar"},
    {SoundId::BassGuitar, "BassGuitar"},
    {SoundId::Banjo, "Banjo"},
    {SoundId::Ukulele, "Ukulele"},
    {SoundId::Mandolin, "Mandolin"},
    {SoundId::MtnDulcimer, "MtnDulcimer"},
    {SoundId::Lute, "Lute"},
    {SoundId::Theorbo, "Theorbo"},
    {SoundId::Archlute, "Archlute"},
    {SoundId::Balalaika, "Balalaika"},
    {SoundId::Koto, "Koto"},
    {SoundId::Oud, "Oud"},
    {SoundId::Shamisen, "Shamisen"},
    {SoundId::Sitar, "Sitar"},
    {SoundId::Prim, "Prim"},
    {SoundId::Brac, "Brac"},
    {SoundId::Bugarija, "Bugarija"},
    {SoundId::Berda, "Berda"},
    {SoundId::Celo, "Celo"},
    {SoundId::Bandurria, "Bandurria"},
    {SoundId::Laud, "Laud"},
    {SoundId::StringsGroup, "StringsGroup"},
    {SoundId::Violin, "Violin"},
    {SoundId::ViolinSection, "ViolinSection"},
    {SoundId::Viola, "Viola"},
    {SoundId::ViolaDaGamba, "ViolaDaGamba"},
    {SoundId::ViolaSection, "ViolaSection"},
    {SoundId::Violoncello, "Violoncello"},
    {SoundId::VioloncelloSection, "VioloncelloSection"},
    {SoundId::Viol, "Viol"},
    {SoundId::PardessusViol, "PardessusViol"},
    {SoundId::Baryton, "Baryton"},
    {SoundId::Violone, "Violone"},
    {SoundId::Nyckelharpa, "Nyckelharpa"},
    {SoundId::Erhu, "Erhu"},
    {SoundId::Contrabass, "Contrabass"},
    {SoundId::ContrabassSection, "ContrabassSection"},
    {SoundId::Octobass, "Octobass"},

    {SoundId::WindsGroup, "WindsGroup"},
    {SoundId::Piccolo, "Piccolo"},
    {SoundId::Heckelphone, "Heckelphone"},
    {SoundId::HeckelphoneClarinet, "HeckelphoneClarinet"},
    {SoundId::Oboe, "Oboe"},
    {SoundId::Lupophone, "Lupophone"},
    {SoundId::Flute, "Flute"},
    {SoundId::PanFlute, "PanFlute"},
    {SoundId::Danso, "Danso"},
    {SoundId::Traverso, "Traverso"},
    {SoundId::Dizi, "Dizi"},
    {SoundId::Shakuhachi, "Shakuhachi"},
    {SoundId::Fife, "Fife"},
    {SoundId::Whistle, "Whistle"},
    {SoundId::Flageolet, "Flageolet"},
    {SoundId::Recorder, "Recorder"},
    {SoundId::Ocarina, "Ocarina"},
    {SoundId::Gemshorn, "Gemshorn"},
    {SoundId::Quena, "Quena"},
    {SoundId::Horn, "Horn"},
    {SoundId::Bassethorn, "Bassethorn"},
    {SoundId::Shawm, "Shawm"},
    {SoundId::Cromorne, "Cromorne"},
    {SoundId::Crumhorn, "Crumhorn"},
    {SoundId::Cornamuse, "Cornamuse"},
    {SoundId::Kelhorn, "Kelhorn"},
    {SoundId::Rauschpfeife, "Rauschpfeife"},
    {SoundId::Duduk, "Duduk"},
    {SoundId::Shenai, "Shenai"},
    {SoundId::Clarinet, "Clarinet"},
    {SoundId::Chalumeau, "Chalumeau"},
    {SoundId::Xaphoon, "Xaphoon"},
    {SoundId::Tarogato, "Tarogato"},
    {SoundId::Octavin, "Octavin"},
    {SoundId::Saxophone, "Saxophone"},
    {SoundId::Aulochrome, "Aulochrome"},
    {SoundId::Bassoon, "Bassoon"},
    {SoundId::Contrabassoon, "Contrabassoon"},
    {SoundId::Dulcian, "Dulcian"},
    {SoundId::Rackett, "Rackett"},
    {SoundId::Sarrusophone, "Sarrusophone"},
    {SoundId::Bagpipe, "Bagpipe"},
    {SoundId::Tuba, "Tuba"},
    {SoundId::Cornet, "Cornet"},
    {SoundId::Posthorn, "Posthorn"},
    {SoundId::BrassGroup, "BrassGroup"},
    {SoundId::Trumpet, "Trumpet"},
    {SoundId::Bugle, "Bugle"},
    {SoundId::MellophoneBugle, "MellophoneBugle"},
    {SoundId::EuphoniumBugle, "EuphoniumBugle"},
    {SoundId::Euphonium, "Euphonium"},
    {SoundId::Fiscorn, "Fiscorn"},
    {SoundId::Flugelhorn, "Flugelhorn"},
    {SoundId::Kuhlohorn, "Kuhlohorn"},
    {SoundId::Ophicleide, "Ophicleide"},
    {SoundId::Cornettino, "Cornettino"},
    {SoundId::Cornett, "Cornett"},
    {SoundId::Serpent, "Serpent"},
    {SoundId::Trombone, "Trombone"},
    {SoundId::Cimbasso, "Cimbasso"},
    {SoundId::Sackbut, "Sackbut"},
    {SoundId::Sousaphone, "Sousaphone"},
    {SoundId::Helicon, "Helicon"},
    {SoundId::Conch, "Conch"},
    {SoundId::Saxhorn, "Saxhorn"},
    {SoundId::Horagai, "Horagai"},
    {SoundId::Alphorn, "Alphorn"},
    {SoundId::RagDung, "RagDung"},
    {SoundId::Didgeridoo, "Didgeridoo"},
    {SoundId::Shofar, "Shofar"},
    {SoundId::Vuvuzela, "Vuvuzela"},

    {SoundId::Timpani, "Timpani"},
    {SoundId::RotoToms, "RotoToms"},
    {SoundId::Tubaphone, "Tubaphone"},
    {SoundId::SteelDrums, "SteelDrums"},
    {SoundId::Glockenspiel, "Glockenspiel"},
    {SoundId::Xylophone, "Xylophone"},
    {SoundId::Xylomarimba, "Xylomarimba"},
    {SoundId::Vibraphone, "Vibraphone"},
    {SoundId::Dulcimer, "Dulcimer"},
    {SoundId::Cimbalom, "Cimbalom"},
    {SoundId::Marimba, "Marimba"},
    {SoundId::Crotales, "Crotales"},
    {SoundId::Chimes, "Chimes"},
    {SoundId::Carillon, "Carillon"},
    {SoundId::Gong, "Gong"},
    {SoundId::Metallophone, "Metallophone"},
    {SoundId::Flexatone, "Flexatone"},
    {SoundId::MusicalSaw, "MusicalSaw"},
    {SoundId::MusicalGlasses, "MusicalGlasses"},
    {SoundId::KlaxonHorns, "KlaxonHorns"},
    {SoundId::Kalimba, "Kalimba"},
    {SoundId::Bongos, "Bongos"},
    {SoundId::TomToms, "TomToms"},
    {SoundId::Conga, "Conga"},
    {SoundId::Cuica, "Cuica"},
    {SoundId::Drumset, "Drumset"},
    {SoundId::Drum, "Drum"},
    {SoundId::Tablas, "Tablas"},
    {SoundId::Timbales, "Timbales"},
    {SoundId::Anvil, "Anvil"},
    {SoundId::Bell, "Bell"},
    {SoundId::Chain, "Chain"},
    {SoundId::Cymbal, "Cymbal"},
    {SoundId::HiHat, "HiHat"},
    {SoundId::Pipe, "Pipe"},
    {SoundId::Castanet, "Castanet"},
    {SoundId::TamTam, "TamTam"},
    {SoundId::Thundersheet, "Thundersheet"},
    {SoundId::Triangle, "Triangle"},
    {SoundId::Claves, "Claves"},
    {SoundId::Guiro, "Guiro"},
    {SoundId::Block, "Block"},
    {SoundId::Cabasa, "Cabasa"},
    {SoundId::Maraca, "Maraca"},
    {SoundId::Quijada, "Quijada"},
    {SoundId::Ratchet, "Ratchet"},
    {SoundId::Shaker, "Shaker"},
    {SoundId::Stones, "Stones"},
    {SoundId::Tambourine, "Tambourine"},
    {SoundId::Tubo, "Tubo"},
    {SoundId::Vibraslap, "Vibraslap"},
    {SoundId::Whip, "Whip"},
    {SoundId::Snap, "Snap"},
    {SoundId::Clap, "Clap"},
    {SoundId::Slap, "Slap"},
    {SoundId::Stamp, "Stamp"},
    {SoundId::Choir, "Choir"},
    {SoundId::Kazoo, "Kazoo"}
};

static const std::map<SoundCategory, std::string> SoundCategoryToString
{
    {SoundCategory::Undefined, "Undefined"},
    {SoundCategory::Keyboards, "Keyboards"},
    {SoundCategory::Strings, "Strings"},
    {SoundCategory::Winds, "Winds"},
    {SoundCategory::Percussions, "Percussions"},
    {SoundCategory::Voices, "Voices"}
};

static const std::map<SoundSubCategory, std::string> SoundSubCategoryToString
{
    {SoundSubCategory::Undefined, "Undefined"},

    {SoundSubCategory::English, "English"},
    {SoundSubCategory::Armenian, "Armenian"},
    {SoundSubCategory::Alpine, "Alpine"},
    {SoundSubCategory::Australian, "Australian"},
    {SoundSubCategory::Irish, "Irish"},
    {SoundSubCategory::French, "French"},
    {SoundSubCategory::Chinese, "Chinese"},
    {SoundSubCategory::Vienna, "Vienna"},
    {SoundSubCategory::Greek, "Greek"},
    {SoundSubCategory::Japanese, "Japanese"},
    {SoundSubCategory::Tibetan, "Tibetan"},
    {SoundSubCategory::African, "African"},
    {SoundSubCategory::Indian, "Indian"},
    {SoundSubCategory::Spanish, "Spanish"},
    {SoundSubCategory::Swedish, "Swedish"},
    {SoundSubCategory::Hungarian, "Hungarian"},
    {SoundSubCategory::Romanian, "Romanian"},
    {SoundSubCategory::CentralEuropean, "CentralEuropean"},

    {SoundSubCategory::Baroque, "Baroque"},
    {SoundSubCategory::Classical, "Classical"},
    {SoundSubCategory::Modern, "Modern"},
    {SoundSubCategory::Orchestral, "Orchestral"},

    {SoundSubCategory::Hammond, "Hammond"},
    {SoundSubCategory::Wagner, "Wagner"},
    {SoundSubCategory::Orff, "Orff"},
    {SoundSubCategory::Huang, "Huang"},
    {SoundSubCategory::Hohner, "Hohner"},

    {SoundSubCategory::Percussive, "Percussive"},
    {SoundSubCategory::Piped, "Piped"},
    {SoundSubCategory::Rotary, "Rotary"},
    {SoundSubCategory::Reed, "Reed"},
    {SoundSubCategory::Foot, "Foot"},
    {SoundSubCategory::Hand, "Hand"},
    {SoundSubCategory::Finger, "Finger"},
    {SoundSubCategory::Boy, "Boy"},
    {SoundSubCategory::Girl, "Girl"},
    {SoundSubCategory::Male, "Male"},
    {SoundSubCategory::Female, "Female"},

    {SoundSubCategory::Temple, "Temple"},
    {SoundSubCategory::Military, "Military"},
    {SoundSubCategory::Ride, "Ride"},
    {SoundSubCategory::Sleigh, "Sleigh"},
    {SoundSubCategory::Cow, "Cow"},
    {SoundSubCategory::Marching, "Marching"},

    {SoundSubCategory::Splash, "Splash"},
    {SoundSubCategory::Crash, "Crash"},
    {SoundSubCategory::Plate, "Plate"},
    {SoundSubCategory::Bowl, "Bowl"},
    {SoundSubCategory::Frame, "Frame"},
    {SoundSubCategory::Slit, "Slit"},
    {SoundSubCategory::Field, "Field"},
    {SoundSubCategory::Snare, "Snare"},
    {SoundSubCategory::Brake, "Brake"},
    {SoundSubCategory::Slide, "Slide"},
    {SoundSubCategory::Pocket, "Pocket"},
    {SoundSubCategory::Garklein, "Garklein"},
    {SoundSubCategory::Toy, "Toy"},
    {SoundSubCategory::TwelveString, "TwelveString"},

    {SoundSubCategory::Grand, "Grand"},
    {SoundSubCategory::HonkyTonk, "HonkyTonk"},
    {SoundSubCategory::Upright, "Upright"},
    {SoundSubCategory::Prima, "Prima"},
    {SoundSubCategory::Secunda, "Secunda"},

    {SoundSubCategory::Electric, "Electric"},
    {SoundSubCategory::Acoustic, "Acoustic"},
    {SoundSubCategory::Pedal, "Pedal"},
    {SoundSubCategory::Steel, "Steel"},
    {SoundSubCategory::Metal, "Metal"},
    {SoundSubCategory::Iron, "Iron"},
    {SoundSubCategory::Brass, "Brass"},
    {SoundSubCategory::Tin, "Tin"},
    {SoundSubCategory::Nylon, "Nylon"},
    {SoundSubCategory::Wooden, "Wooden"},
    {SoundSubCategory::Sandpaper, "Sandpaper"},
    {SoundSubCategory::Glass, "Glass"},
    {SoundSubCategory::Shell, "Shell"},
    {SoundSubCategory::Wind, "Wind"},

    {SoundSubCategory::Treble, "Treble"},
    {SoundSubCategory::Diatonic, "Diatonic"},
    {SoundSubCategory::Chromatic, "Chromatic"},
    {SoundSubCategory::Octave, "Octave"},

    {SoundSubCategory::Piccolo, "Piccolo"},
    {SoundSubCategory::Alto, "Alto"},
    {SoundSubCategory::Tenor, "Tenor"},
    {SoundSubCategory::Baritone, "Baritone"},
    {SoundSubCategory::Soprano, "Soprano"},
    {SoundSubCategory::Mezzo_Soprano, "Mezzo_Soprano"},
    {SoundSubCategory::Sopranino, "Sopranino"},
    {SoundSubCategory::Sopranissimo, "Sopranissimo"},
    {SoundSubCategory::Counter_Tenor, "Counter_Tenor"},
    {SoundSubCategory::Contra, "Contra"},
    {SoundSubCategory::Contra_Alto, "Contra_Alto"},
    {SoundSubCategory::Sub_Contra_Alto, "Sub_Contra_Alto"},
    {SoundSubCategory::Contra_Bass, "Contra_Bass"},
    {SoundSubCategory::Sub_Contra_Bass, "Sub_Contra_Bass"},
    {SoundSubCategory::Double_Contra_Bass, "Double_Contra_Bass"},
    {SoundSubCategory::Bass, "Bass"},
    {SoundSubCategory::Great_Bass, "Great_Bass"},
    {SoundSubCategory::Hyper_Bass, "Hyper_Bass"},
    {SoundSubCategory::Melody, "Melody"},

    {SoundSubCategory::FX_Goblins, "FX_Goblins"},
    {SoundSubCategory::FX_Atmosphere, "FX_Atmosphere"},
    {SoundSubCategory::FX_Brightness, "FX_Brightness"},
    {SoundSubCategory::FX_Crystal, "FX_Crystal"},
    {SoundSubCategory::FX_Echoes, "FX_Echoes"},
    {SoundSubCategory::FX_Rain, "FX_Rain"},
    {SoundSubCategory::FX_SciFi, "FX_SciFi"},
    {SoundSubCategory::FX_SoundTrack, "FX_SoundTrack"}
};

inline std::string SoundSubCategoriesToString(SoundSubCategories subcategories) {
    std::string subcat_ids;
    for (auto sc : subcategories)
        subcat_ids = subcat_ids + mpe::SoundSubCategoryToString.at(sc) + ",";
    if (!subcat_ids.empty())
        subcat_ids = subcat_ids.substr(0, subcat_ids.size() - 1);
    return subcat_ids;
};

inline std::string MpeIdToString(SoundId id, SoundCategory category, const SoundSubCategories& subcategories) {
  std::string res;
  if (SoundIdToString.count(id) > 0)
      res += SoundIdToString.at(id);
  res += ".";
  if (SoundCategoryToString.count(category) > 0)
      res += SoundCategoryToString.at(category);
  res += ".";
  return res + SoundSubCategoriesToString(subcategories);
}

} // namespace mu::mpe

#endif // MU_SOUNDID_STRINGIFY_H
