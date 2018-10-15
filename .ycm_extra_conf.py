# This file is NOT licensed under the GPLv3, which is the license for the rest
# of YouCompleteMe.
#
# Here's the license text for this file:
#
# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

import os
import ycm_core

# These are the compilation flags that will be used in case there's no
# compilation database set (by default, one is not set).
# CHANGE THIS LIST OF FLAGS. YES, THIS IS THE DROID YOU HAVE BEEN LOOKING FOR.
flags = [
'-Wall',
'-Wextra',
'-Werror',
#'-Wno-long-long',
#'-Wno-variadic-macros',
#'-fexceptions',
#'-DNDEBUG',
# You 100% do NOT need -DUSE_CLANG_COMPLETER in your flags; only the YCM
# source code needs it.
'-DUSE_CLANG_COMPLETER',
  "-x",
  "c++",
  "-std=gnu++14",
  "-I/home/hg/UnrealEngine/Engine/Source",
  "-I/home/hg/Scrapyard/Source/Scrapyard/Private",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Application",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Commands",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Docking",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Layout",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/MetaData",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/MultiBox",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Notifications",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Styling",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Text",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Framework/Views",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Colors",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Docking",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Images",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Input",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/LayerManager",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Layout",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Navigation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Notifications",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Text",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Slate/Public/Widgets/Views",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Linux",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Algo",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Algo/Impl",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Async",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Clang",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Containers",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Delegates",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Features",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/FramePro",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/GenericPlatform",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/HAL",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/HAL/Allocators",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Hash",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Internationalization",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Logging",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Math",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Misc",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Modules",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Modules/Boilerplate",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/ProfilingDebugging",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Serialization",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Serialization/Csv",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Serialization/Formatters",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Stats",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Templates",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Traits",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/UObject",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Core/Public/Unix",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/Blueprint",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/Internationalization",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/Misc",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/Serialization",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/Serialization/Formatters",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/Templates",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/CoreUObject/Public/UObject",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ApplicationCore/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ApplicationCore",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ApplicationCore/Public/GenericPlatform",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ApplicationCore/Public/HAL",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ApplicationCore/Public/Linux",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ApplicationCore/Public/Unix",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/RHI/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/RHI",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/InputCore/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/InputCore/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/InputCore",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/InputCore/Public/GenericPlatform",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/InputCore/Public/HAL",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/InputCore/Public/Linux",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Json/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Json",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Json/Public/Dom",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Json/Public/Policies",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Json/Public/Serialization",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Animation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Application",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Brushes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Fonts",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Input",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Layout",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Logging",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Rendering",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Sound",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Stats",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Styling",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Textures",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Types",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SlateCore/Public/Widgets",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ImageWrapper/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ImageWrapper",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystem",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystem/Source",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystem/Source/Public",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystem/Source/Public/Interfaces",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystemUtils/Source",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public",
  "-I/home/hg/UnrealEngine/Engine/Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/AI",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/AI/Navigation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Animation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Curves",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/EdGraph",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Internationalization",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Net",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/PacketHandlers",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Performance",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Physics",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/ProfilingDebugging",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Rendering",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Slate",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/Tests",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Engine/Public/VisualLogger",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Messaging/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Messaging",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MessagingCommon/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MessagingCommon",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/RenderCore/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/RenderCore",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ShaderCore/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ShaderCore",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UtilityShaders/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UtilityShaders",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AssetRegistry/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AssetRegistry",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/EngineMessages/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/EngineMessages",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/EngineSettings/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/EngineSettings/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/EngineSettings",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SynthBenchmark/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SynthBenchmark",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Renderer/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Renderer",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/GameplayTags/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/GameplayTags/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/GameplayTags",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/DatabaseSupport/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/DatabaseSupport",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PacketHandlers",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PacketHandlers/PacketHandler/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PacketHandlers/PacketHandler/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PacketHandlers/PacketHandler",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PacketHandlers/ReliabilityHandlerComponent/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PacketHandlers/ReliabilityHandlerComponent",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioPlatformConfiguration/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioPlatformConfiguration",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MeshDescription/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MeshDescription",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor",
  "-I/home/hg/UnrealEngine/Engine/Source/Programs/UnrealLightmass/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/AutoReimport",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Commandlets",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Dialogs",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/DragAndDrop",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Features",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Kismet2",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Layers",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Settings",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Tests",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEd/Public/Toolkits",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/BspMode/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/BspMode",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/DirectoryWatcher/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/DirectoryWatcher",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Documentation/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Documentation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Projects/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Projects",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Projects/Public/Interfaces",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SandboxFile/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/SandboxFile",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/EditorStyle/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/EditorStyle",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/EditorStyle/Public/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/EditorStyle/Public/Interfaces",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/SourceControl/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/SourceControl",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/SourceControl/Public/Tests",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEdMessages/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEdMessages/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/UnrealEdMessages",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/GameplayDebugger/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/GameplayDebugger",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/BlueprintGraph/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/BlueprintGraph/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/BlueprintGraph",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Online",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Online/HTTP/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Online/HTTP",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Online/HTTP/Public/GenericPlatform",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Online/HTTP/Public/Interfaces",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Online/HTTP/Public/Unix",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UnrealAudio/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UnrealAudio",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/FunctionalTesting/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/FunctionalTesting/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/FunctionalTesting",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/AutomationController/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/AutomationController",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/Localization/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/Localization",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/Localization/Public/Serialization",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/AudioEditor/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/AudioEditor/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/AudioEditor",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/AudioEditor/Public/AssetTypeActions",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/LevelEditor/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/LevelEditor",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/Settings/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/Settings",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/IntroTutorials/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/IntroTutorials",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/HeadMountedDisplay/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/HeadMountedDisplay",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/VREditor",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/VREditor/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/CommonMenuExtensions/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/CommonMenuExtensions",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Landscape/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Landscape/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Landscape",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/PropertyEditor/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/PropertyEditor",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/ActorPickerMode/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/ActorPickerMode",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/SceneDepthPickerMode/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/SceneDepthPickerMode",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/DetailCustomizations/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/DetailCustomizations",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/DetailCustomizations/Public/Customizations",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/ClassViewer/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/ClassViewer",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/GraphEditor/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/GraphEditor",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/GraphEditor/Public/KismetNodes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/GraphEditor/Public/KismetPins",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/ContentBrowser/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/ContentBrowser",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NetworkFileSystem/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NetworkFileSystem",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Sockets/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/Sockets",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG/Public/Animation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG/Public/Binding",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG/Public/Blueprint",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG/Public/Components",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/UMG/Public/Slate",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Channels",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Compilation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Evaluation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Evaluation/Blending",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Generators",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Sections",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieScene/Public/Tracks",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/TimeManagement/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/TimeManagement",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/TimeManagement/Public/Widgets",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieSceneTracks/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieSceneTracks",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieSceneTracks/Public/Evaluation",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieSceneTracks/Public/Sections",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/MovieSceneTracks/Public/Tracks",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AnimationCore/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AnimationCore",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PropertyPath/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/PropertyPath",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NavigationSystem/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NavigationSystem",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NavigationSystem/Public/NavAreas",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NavigationSystem/Public/NavFilters",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NavigationSystem/Public/NavGraph",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NavigationSystem/Public/NavMesh",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshBuilder/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshBuilder",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/CollectionManager/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/CollectionManager",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/AddContentDialog/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/AddContentDialog",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshUtilities/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshUtilities",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshMergeUtilities/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshMergeUtilities",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/HierarchicalLODUtilities/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/HierarchicalLODUtilities",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshReductionInterface/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/MeshReductionInterface",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/AssetTools/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/AssetTools",
  "-I/home/hg/UnrealEngine/Engine/Source/Developer/AssetTools/Public/AssetTypeActions",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/KismetCompiler/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/KismetCompiler",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/GameplayTasks/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/GameplayTasks/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/GameplayTasks",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AIModule/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AIModule/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AIModule",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Kismet/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Kismet/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Kismet",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Kismet/Public/Nodes",
  "-I/home/hg/UnrealEngine/Engine/Source/Editor/Kismet/Public/WorkflowOrientedApp",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ClothingSystemRuntimeInterface/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/ClothingSystemRuntimeInterface",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NetworkReplayStreaming",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NetworkReplayStreaming/NetworkReplayStreaming/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/NetworkReplayStreaming/NetworkReplayStreaming",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioMixer/Classes",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioMixer/Public",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioMixer",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioMixer/Public/Components",
  "-I/home/hg/UnrealEngine/Engine/Source/Runtime/AudioMixer/Public/DSP",
#  "-I/home/hg/Scrapyard/Source",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public",
#  "-I/home/hg/Scrapyard/Source/Scrapyard",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Ability",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Game",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Levels",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Online",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Parts",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Parts/Arms",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Parts/Core",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Parts/Handheld",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Parts/Head",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Parts/Legs",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Player",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/Robots",
#  "-I/home/hg/Scrapyard/Source/Scrapyard/Public/UI",
#  "-I/home/hg/Scrapyard/Source/ScrapyardServer/Private",
#  "-I/home/hg/Scrapyard/Source/ScrapyardServer/Public",
#  "-I/home/hg/Scrapyard/Source/ScrapyardServer",
#  "-I/home/hg/Scrapyard/Source/ScrapyardClient/Private",
#  "-I/home/hg/Scrapyard/Source/ScrapyardClient/Public",
#  "-I/home/hg/Scrapyard/Source/ScrapyardClient",
  "-I/usr/include",
  "-I/usr/local/include"
]


# Set this to the absolute path to the folder (NOT the file!) containing the
# compile_commands.json file to use that instead of 'flags'. See here for
# more details: http://clang.llvm.org/docs/JSONCompilationDatabase.html
#
# You can get CMake to generate this file for you by adding:
#   set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
# to your CMakeLists.txt file.
#
# Most projects will NOT need to set this to anything; you can just change the
# 'flags' list of compilation flags. Notice that YCM itself uses that approach.
compilation_database_folder = '/home/hg/Scrapyard/'

if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def gen_recursive_include_path(dir):
  subdirs = [x[0] for x in os.walk(dir) if "CMake" not in x[0]]
  include_path = []
  for x in subdirs:
    include_path.extend(['-I', x])
  return include_path

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )
      new_flag = '"' + new_flag + '"'

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        if not path.startswith( '/' ):
          new_flag = '"' + path_flag + os.path.join( working_directory, path ) + '"'
        else:
          new_flag = '"' + flag + '"'
        break

    if new_flag:
      print(new_flag)
      new_flags.append( new_flag )
  return new_flags


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]


def GetCompilationInfoForFile( filename ):
  # The compilation_commands.json file generated by CMake does not have entries
  # for header files. So we do our best by asking the db for flags for a
  # corresponding source file, if any. If one exists, the flags for that file
  # should be good enough.
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        compilation_info = database.GetCompilationInfoForFile(
          replacement_file )
        if compilation_info.compiler_flags_:
          return compilation_info
    return None
  return database.GetCompilationInfoForFile( filename )


def FlagsForFile( filename, **kwargs ):
  if database:
    # Bear in mind that compilation_info.compiler_flags_ does NOT return a
    # python list, but a "list-like" StringVec object
    compilation_info = GetCompilationInfoForFile( filename )
    if not compilation_info:
      return None

    final_flags = MakeRelativePathsInFlagsAbsolute(
      compilation_info.compiler_flags_,
      compilation_info.compiler_working_dir_ )

  else:
    print('no database')
    relative_to = DirectoryOfThisScript()
    final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )
#    final_flags = final_flags + gen_recursive_include_path('/Users/Shared/Epic Games/UE_4.15/Engine')
  final_flags = final_flags + gen_recursive_include_path('/home/hg/Scrapyard/Source')
  final_flags = final_flags + gen_recursive_include_path('/home/hg/Scrapyard/Intermediate/Build/Linux/B4D820EA')
  final_flags = final_flags + flags

  return { 'flags': final_flags }
