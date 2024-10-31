/*
 * Copyright (c) 2022, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/TypeCasts.h>
#include <LibJS/Heap/GCPtr.h>
#include <LibJS/Runtime/Realm.h>
#include <LibWeb/Forward.h>

namespace Web::Bindings {

struct PrincipalHostDefined : public JS::Realm::HostDefined {
    PrincipalHostDefined(JS::NonnullGCPtr<HTML::EnvironmentSettingsObject> eso, JS::NonnullGCPtr<Intrinsics> intrinsics, JS::NonnullGCPtr<Page> page)
        : environment_settings_object(eso)
        , intrinsics(intrinsics)
        , page(page)
    {
    }
    virtual ~PrincipalHostDefined() override = default;
    virtual void visit_edges(JS::Cell::Visitor& visitor) override;

    JS::NonnullGCPtr<HTML::EnvironmentSettingsObject> environment_settings_object;
    JS::NonnullGCPtr<Intrinsics> intrinsics;
    JS::NonnullGCPtr<Page> page;
};

[[nodiscard]] inline HTML::EnvironmentSettingsObject& principal_host_defined_environment_settings_object(JS::Realm& realm)
{
    return *verify_cast<PrincipalHostDefined>(realm.host_defined())->environment_settings_object;
}

[[nodiscard]] inline HTML::EnvironmentSettingsObject const& principal_host_defined_environment_settings_object(JS::Realm const& realm)
{
    return *verify_cast<PrincipalHostDefined>(realm.host_defined())->environment_settings_object;
}

[[nodiscard]] inline Page& principal_host_defined_page(JS::Realm& realm)
{
    return *verify_cast<PrincipalHostDefined>(realm.host_defined())->page;
}

}