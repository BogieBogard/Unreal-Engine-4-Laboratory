// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeshEditorStaticMeshAdapter.h"
#include "EditableMesh.h"
#include "MeshAttributes.h"
#include "WireframeMeshComponent.h"


static FColor GetEdgeColor( bool bIsHardEdge, bool bIsUVSeam )
{
	if( bIsUVSeam )
	{
		return bIsHardEdge ? FColor( 20, 80, 25 ) : FColor( 0, 46, 10 );
	}
	else
	{
		return bIsHardEdge ? FColor( 20, 20, 128 ) : FColor( 0, 0, 76 );
	}
}


UMeshEditorStaticMeshAdapter::UMeshEditorStaticMeshAdapter()
{
}


void UMeshEditorStaticMeshAdapter::Initialize( UEditableMesh* EditableMesh, UWireframeMesh* InWireframeMesh )
{
	WireframeMesh = InWireframeMesh;
}


void UMeshEditorStaticMeshAdapter::OnRebuildRenderMeshStart( const UEditableMesh* EditableMesh, const bool bInvalidateLighting )
{
	for( TObjectIterator<UWireframeMeshComponent> It( RF_ClassDefaultObject, false, EInternalObjectFlags::PendingKill ); It; ++It )
	{
		if( It->GetWireframeMesh() == WireframeMesh )
		{
			if( It->IsRenderStateCreated() )
			{
				check( It->IsRegistered() );
				It->UnregisterComponent();
			}
		}
	}

	WireframeMesh->ReleaseResources();

	// Flush the rendering commands generated by the detachments.
	FlushRenderingCommands();
}


void UMeshEditorStaticMeshAdapter::OnRebuildRenderMesh( const UEditableMesh* EditableMesh )
{
	WireframeMesh->Reset();

	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	// Add all vertices
	const TVertexAttributeArray<FVector>& VertexPositions = MeshDescription->VertexAttributes().GetAttributes<FVector>( MeshAttribute::Vertex::Position );
	for( const FVertexID VertexID : MeshDescription->Vertices().GetElementIDs() )
	{
		WireframeMesh->AddVertex( VertexID );
		WireframeMesh->SetVertexPosition( VertexID, VertexPositions[ VertexID ] );
	}

	// Add all edges
	const TEdgeAttributeArray<bool>& EdgeHardnesses = MeshDescription->EdgeAttributes().GetAttributes<bool>( MeshAttribute::Edge::IsHard );
	const TEdgeAttributeArray<bool>& EdgeUVSeams = MeshDescription->EdgeAttributes().GetAttributes<bool>( MeshAttribute::Edge::IsUVSeam );
	for( const FEdgeID EdgeID : MeshDescription->Edges().GetElementIDs() )
	{
		WireframeMesh->AddEdge( EdgeID );
		WireframeMesh->SetEdgeVertices( EdgeID, EditableMesh->GetEdgeVertex( EdgeID, 0 ), EditableMesh->GetEdgeVertex( EdgeID, 1 ) );
		WireframeMesh->SetEdgeColor( EdgeID, GetEdgeColor( EdgeHardnesses[ EdgeID ], EdgeUVSeams[ EdgeID ] ) );
	}

	// Add all polygons and edge instances
	// @todo mesheditor wireframe: holes not yet handled
	const TPolygonAttributeArray<FVector>& PolygonNormals = MeshDescription->PolygonAttributes().GetAttributes<FVector>( MeshAttribute::Polygon::Normal );
	for( const FPolygonID PolygonID : EditableMesh->GetMeshDescription()->Polygons().GetElementIDs() )
	{
		WireframeMesh->AddPolygon( PolygonID );
		WireframeMesh->SetPolygonNormal( PolygonID, PolygonNormals[ PolygonID ] );

		const int32 NumEdges = EditableMesh->GetPolygonPerimeterEdgeCount( PolygonID );
		for( int32 Index = 0; Index < NumEdges; ++Index )
		{
			bool bOutWindingIsReversed;
			WireframeMesh->AddEdgeInstance( EditableMesh->GetPolygonPerimeterEdge( PolygonID, Index, bOutWindingIsReversed ), PolygonID );
		}
	}
}


void UMeshEditorStaticMeshAdapter::OnRebuildRenderMeshFinish( const UEditableMesh* EditableMesh, const bool bRebuildBoundsAndCollision, const bool bIsPreviewRollback )
{
	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	const TPolygonAttributeArray<FVector>& PolygonNormals = MeshDescription->PolygonAttributes().GetAttributes<FVector>( MeshAttribute::Polygon::Normal );
	for( const FPolygonID PolygonID : EditableMesh->PolygonsPendingNewTangentBasis )
	{
		WireframeMesh->SetPolygonNormal( PolygonID, PolygonNormals[ PolygonID ] );
	}

	WireframeMesh->InitResources();

	for( TObjectIterator<UWireframeMeshComponent> It( RF_ClassDefaultObject, false, EInternalObjectFlags::PendingKill ); It; ++It )
	{
		if( It->GetWireframeMesh() == WireframeMesh )
		{
			if( !It->IsRenderStateCreated() )
			{
				It->RegisterComponent();
			}
		}
	}
}


void UMeshEditorStaticMeshAdapter::OnStartModification( const UEditableMesh* EditableMesh, const EMeshModificationType MeshModificationType, const EMeshTopologyChange MeshTopologyChange )
{
}


void UMeshEditorStaticMeshAdapter::OnEndModification( const UEditableMesh* EditableMesh )
{
}


void UMeshEditorStaticMeshAdapter::OnReindexElements( const UEditableMesh* EditableMesh, const FElementIDRemappings& Remappings )
{
}


bool UMeshEditorStaticMeshAdapter::IsCommitted( const UEditableMesh* EditableMesh ) const
{
	return false;
}


bool UMeshEditorStaticMeshAdapter::IsCommittedAsInstance( const UEditableMesh* EditableMesh ) const
{
	return false;
}


void UMeshEditorStaticMeshAdapter::OnCommit( UEditableMesh* EditableMesh )
{
}


UEditableMesh* UMeshEditorStaticMeshAdapter::OnCommitInstance( UEditableMesh* EditableMesh, UPrimitiveComponent* ComponentToInstanceTo )
{
	return nullptr;
}


void UMeshEditorStaticMeshAdapter::OnRevert( UEditableMesh* EditableMesh )
{
}


UEditableMesh* UMeshEditorStaticMeshAdapter::OnRevertInstance( UEditableMesh* EditableMesh )
{
	return nullptr;
}


void UMeshEditorStaticMeshAdapter::OnPropagateInstanceChanges( UEditableMesh* EditableMesh )
{
}


void UMeshEditorStaticMeshAdapter::OnDeleteVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs )
{
}


void UMeshEditorStaticMeshAdapter::OnDeleteOrphanVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs )
{
	for( const FVertexID VertexID : VertexIDs )
	{
		WireframeMesh->RemoveVertex( VertexID );
	}
}


void UMeshEditorStaticMeshAdapter::OnCreateEmptyVertexRange( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs )
{
	for( const FVertexID VertexID : VertexIDs )
	{
		WireframeMesh->AddVertex( VertexID );
	}
}


void UMeshEditorStaticMeshAdapter::OnCreateVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs )
{
	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	const TVertexAttributeArray<FVector>& VertexPositions = MeshDescription->VertexAttributes().GetAttributes<FVector>( MeshAttribute::Vertex::Position );
	for( const FVertexID VertexID : VertexIDs )
	{
		WireframeMesh->AddVertex( VertexID );
		WireframeMesh->SetVertexPosition( VertexID, VertexPositions[ VertexID ] );
	}
}


void UMeshEditorStaticMeshAdapter::OnCreateVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs )
{
}


void UMeshEditorStaticMeshAdapter::OnSetVertexAttribute( const UEditableMesh* EditableMesh, const FVertexID VertexID, const FMeshElementAttributeData& Attribute )
{
	if( Attribute.AttributeName == MeshAttribute::Vertex::Position )
	{
		WireframeMesh->SetVertexPosition( VertexID, Attribute.AttributeValue.GetValue<FVector>() );
	}
}


void UMeshEditorStaticMeshAdapter::OnCreateEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs )
{
	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	const TEdgeAttributeArray<bool>& EdgeHardnesses = MeshDescription->EdgeAttributes().GetAttributes<bool>( MeshAttribute::Edge::IsHard );
	const TEdgeAttributeArray<bool>& EdgeUVSeams = MeshDescription->EdgeAttributes().GetAttributes<bool>( MeshAttribute::Edge::IsUVSeam );

	for( const FEdgeID EdgeID : EdgeIDs )
	{
		WireframeMesh->AddEdge( EdgeID );
		WireframeMesh->SetEdgeVertices( EdgeID, EditableMesh->GetEdgeVertex( EdgeID, 0 ), EditableMesh->GetEdgeVertex( EdgeID, 1 ) );
		WireframeMesh->SetEdgeColor( EdgeID, GetEdgeColor( EdgeHardnesses[ EdgeID ], EdgeUVSeams[ EdgeID ] ) );

		for( const FPolygonID PolygonID : MeshDescription->GetEdgeConnectedPolygons( EdgeID ) )
		{
			WireframeMesh->AddEdgeInstance( EdgeID, PolygonID );
		}
	}
}


void UMeshEditorStaticMeshAdapter::OnDeleteEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs )
{
	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	for( const FEdgeID EdgeID : EdgeIDs )
	{
		for( const FPolygonID PolygonID : MeshDescription->GetEdgeConnectedPolygons( EdgeID ) )
		{
			WireframeMesh->RemoveEdgeInstance( EdgeID, PolygonID );
		}

		WireframeMesh->RemoveEdge( EdgeID );
	}
}


void UMeshEditorStaticMeshAdapter::OnSetEdgesVertices( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs )
{
	for( const FEdgeID EdgeID : EdgeIDs )
	{
		WireframeMesh->SetEdgeVertices( EdgeID, EditableMesh->GetEdgeVertex( EdgeID, 0 ), EditableMesh->GetEdgeVertex( EdgeID, 1 ) );
	}
}


void UMeshEditorStaticMeshAdapter::OnSetEdgeAttribute( const UEditableMesh* EditableMesh, const FEdgeID EdgeID, const FMeshElementAttributeData& Attribute )
{
	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	const TEdgeAttributeArray<bool>& EdgeHardnesses = MeshDescription->EdgeAttributes().GetAttributes<bool>( MeshAttribute::Edge::IsHard );
	const TEdgeAttributeArray<bool>& EdgeUVSeams = MeshDescription->EdgeAttributes().GetAttributes<bool>( MeshAttribute::Edge::IsUVSeam );

	if( Attribute.AttributeName == MeshAttribute::Edge::IsHard ||
		Attribute.AttributeName == MeshAttribute::Edge::IsUVSeam )
	{
		WireframeMesh->SetEdgeColor( EdgeID, GetEdgeColor( EdgeHardnesses[ EdgeID ], EdgeUVSeams[ EdgeID ] ) );
	}
}


void UMeshEditorStaticMeshAdapter::OnCreatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
	const FMeshDescription* MeshDescription = EditableMesh->GetMeshDescription();
	check( MeshDescription );

	const TPolygonAttributeArray<FVector>& PolygonNormals = MeshDescription->PolygonAttributes().GetAttributes<FVector>( MeshAttribute::Polygon::Normal );
	for( const FPolygonID PolygonID : PolygonIDs )
	{
		WireframeMesh->AddPolygon( PolygonID );
		WireframeMesh->SetPolygonNormal( PolygonID, PolygonNormals[ PolygonID ] );

		const int32 NumEdges = EditableMesh->GetPolygonPerimeterEdgeCount( PolygonID );
		for( int32 Index = 0; Index < NumEdges; ++Index )
		{
			bool bOutWindingIsReversed;
			WireframeMesh->AddEdgeInstance( EditableMesh->GetPolygonPerimeterEdge( PolygonID, Index, bOutWindingIsReversed ), PolygonID );
		}
	}
}


void UMeshEditorStaticMeshAdapter::OnDeletePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
	for( const FPolygonID PolygonID : PolygonIDs )
	{
		const int32 NumEdges = EditableMesh->GetPolygonPerimeterEdgeCount( PolygonID );
		for( int32 Index = 0; Index < NumEdges; ++Index )
		{
			bool bOutWindingIsReversed;
			WireframeMesh->RemoveEdgeInstance( EditableMesh->GetPolygonPerimeterEdge( PolygonID, Index, bOutWindingIsReversed ), PolygonID );
		}

		WireframeMesh->RemovePolygon( PolygonID );
	}
}


void UMeshEditorStaticMeshAdapter::OnChangePolygonVertexInstances( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
}


void UMeshEditorStaticMeshAdapter::OnCreatePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs )
{
}


void UMeshEditorStaticMeshAdapter::OnDeletePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs )
{
}


void UMeshEditorStaticMeshAdapter::OnRetriangulatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
}
