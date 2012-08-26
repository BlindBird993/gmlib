# ###############################################################################
# #
# # Copyright (C) 1994 Narvik University College
# # Contact: GMlib Online Portal at http://episteme.hin.no
# #
# # This file is part of the Geometric Modeling Library, GMlib.
# #
# # GMlib is free software: you can redistribute it and/or modify
# # it under the terms of the GNU Lesser General Public License as published by
# # the Free Software Foundation, either version 3 of the License, or
# # (at your option) any later version.
# #
# # GMlib is distributed in the hope that it will be useful,
# # but WITHOUT ANY WARRANTY; without even the implied warranty of
# # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# # GNU Lesser General Public License for more details.
# #
# # You should have received a copy of the GNU Lesser General Public License
# # along with GMlib. If not, see <http://www.gnu.org/licenses/>.
# #
# ###############################################################################


################################
# Process each individual module
# addModule( ModuleName [DependModuleName 1] [DependModuleName 2] ... )


# Add core module
addModule(Core)

# Add OpenGL module
addModule(OpenGL Core)

# Add Scene module
addModule(Scene Core OpenGL)

# Add Parametrics module
addModule(Parametrics Core OpenGL Scene)

# Add TringleSystem module
addModule(TriangleSystem Core OpenGL Scene)

# Add STereoLithography module
addModule(StereoLithography Core SceneParametrics TriangleSystem)

# Add Window module
addModule(Window Core OpenGL Scene)

# Add Script module
addModule(Script Core)

